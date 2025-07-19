// raycaster.c

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_data {
    void      *mlx, *win, *img;
    char      *addr;
    int        bpp, line_len, endian;
    double     posX, posY;
    double     dirX, dirY;
    double     planeX, planeY;
    int        keys[65536];
    t_cub3d   *cub3d;         // ← new: pointer to your parsed data
    int        mapW, mapH;    // ← dynamic map dimensions
    int        scale;         // ← pixel size of each cell on the minimap
    int        miniW;         // ← minimap width in pixels (mapW*scale)
    int        viewW;         // ← width of the 3D view
    int        winW, winH;    // ← total window dims
} t_data;

// ─── Pixel Helpers ─────────────────────────────────────────────────────────────

static void put_pixel(t_data *d, int x, int y, int color) {
    if (x < 0 || x >= d->winW || y < 0 || y >= d->winH) return;
    char *dst = d->addr + (y * d->line_len + x * (d->bpp/8));
    *(unsigned int*)dst = color;
}

static void draw_rect(t_data *d, int x, int y, int w, int h, int color) {
    for(int i = 0; i < w; ++i)
      for(int j = 0; j < h; ++j)
        put_pixel(d, x+i, y+j, color);
}

static void draw_line(t_data *d, int x0,int y0,int x1,int y1,int col) {
    int dx = abs(x1-x0), sx = x0<x1 ? 1:-1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1:-1;
    int err = dx + dy, e2;
    while (1) {
        put_pixel(d, x0, y0, col);
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

// ─── Input ─────────────────────────────────────────────────────────────────────

static int key_press(int kc, t_data *d) {
    if (kc == KEY_ESC) exit(0);
    d->keys[kc] = 1;
    return 0;
}
static int key_release(int kc, t_data *d) {
    d->keys[kc] = 0;
    return 0;
}

// ─── Movement ──────────────────────────────────────────────────────────────────

static void move_player(t_data *d, double dt) {
    double ms = dt * 5.0;
    double rs = dt * 3.0;

    // forward/back
    if (d->keys[KEY_W] || d->keys[KEY_UP]) {
        if (!d->cub3d->point[(int)(d->posY)][(int)(d->posX + d->dirX*ms)].access)
            d->posX += d->dirX*ms;
        if (!d->cub3d->point[(int)(d->posY + d->dirY*ms)][(int)(d->posX)].access)
            d->posY += d->dirY*ms;
    }
    if (d->keys[KEY_S] || d->keys[KEY_DOWN]) {
        if (!d->cub3d->point[(int)(d->posY)][(int)(d->posX - d->dirX*ms)].access)
            d->posX -= d->dirX*ms;
        if (!d->cub3d->point[(int)(d->posY - d->dirY*ms)][(int)(d->posX)].access)
            d->posY -= d->dirY*ms;
    }
    // strafe
    if (d->keys[KEY_A] || d->keys[KEY_D]) {
        double sx = (d->keys[KEY_A] ?  1 : -1) * d->dirY * ms;
        double sy = (d->keys[KEY_A] ? -1 :  1) * d->dirX * ms;
        if (!d->cub3d->point[(int)(d->posY)][(int)(d->posX + sx)].access)
            d->posX += sx;
        if (!d->cub3d->point[(int)(d->posY + sy)][(int)(d->posX)].access)
            d->posY += sy;
    }
    // rotate
    if (d->keys[KEY_LEFT] || d->keys[KEY_RIGHT]) {
        double ang = (d->keys[KEY_RIGHT] ? -rs : rs);
        double odx = d->dirX, opx = d->planeX;
        d->dirX   = d->dirX * cos(ang) - d->dirY * sin(ang);
        d->dirY   = odx      * sin(ang) + d->dirY * cos(ang);
        d->planeX = d->planeX * cos(ang) - d->planeY * sin(ang);
        d->planeY = opx      * sin(ang) + d->planeY * cos(ang);
    }
}

// ─── Rendering ────────────────────────────────────────────────────────────────

static int render_frame(void *param) {
    t_data *d = param;
    static double last = 0;
    double now  = (double)clock() / CLOCKS_PER_SEC;
    double dt   = now - last;
    last = now;

    move_player(d, dt);

    // 1) draw 2D minimap
    for(int y=0; y<d->mapH; y++){
      for(int x=0; x<d->mapW; x++){
        int access = d->cub3d->point[y][x].access;
        int col = access ? 0x777777 : 0x222222;
        draw_rect(d,
          x*d->scale, y*d->scale,
          d->scale,  d->scale,
          col
        );
      }
    }
    // player dot
    int px = d->posX * d->scale;
    int py = d->posY * d->scale;
    draw_rect(d, px-2, py-2, 4, 4, 0x00FF00);

    // 2) sky & floor
    for(int y=0; y<d->winH/2; y++)
      for(int x=d->miniW; x<d->winW; x++)
        put_pixel(d,x,y,0x87CEEB);
    for(int y=d->winH/2; y<d->winH; y++)
      for(int x=d->miniW; x<d->winW; x++)
        put_pixel(d,x,y,0x888888);

    // 3) raycast each vertical stripe
    for(int stripe=0; stripe<d->viewW; stripe++){
      double camX  = 2*stripe/(double)d->viewW - 1;
      double rayX  = d->dirX + d->planeX * camX;
      double rayY  = d->dirY + d->planeY * camX;
      int mapX = (int)d->posX, mapY = (int)d->posY;
      double dX = fabs(rayX) < 1e-6 ? 1e30 : fabs(1/rayX);
      double dY = fabs(rayY) < 1e-6 ? 1e30 : fabs(1/rayY);

      int stepX = rayX<0 ? -1 : 1;
      int stepY = rayY<0 ? -1 : 1;
      double sX = (rayX<0
                   ? (d->posX - mapX)*dX
                   : (mapX+1 - d->posX)*dX);
      double sY = (rayY<0
                   ? (d->posY - mapY)*dY
                   : (mapY+1 - d->posY)*dY);

      int hit=0, side=0;
      while(!hit){
        if (sX < sY) { sX += dX; mapX += stepX; side = 0; }
        else         { sY += dY; mapY += stepY; side = 1; }
        if (d->cub3d->point[mapY][mapX].access > 0) hit = 1;
      }

      double perp = side==0
                  ? (sX - dX)
                  : (sY - dY);

      // draw the ray on minimap
      double hx = d->posX + rayX * perp;
      double hy = d->posY + rayY * perp;
      draw_line(d, px, py,
                   hx * d->scale,
                   hy * d->scale,
                   0xFF0000);

      // vertical slice
      int h = (int)(d->winH / perp);
      int start = -h/2 + d->winH/2;
      int end   =  h/2 + d->winH/2;
      if (start<0) start=0;
      if (end>=d->winH) end=d->winH-1;

      int color = 0xFFFFFF / d->cub3d->point[mapY][mapX].access;
      if (side)  color >>= 1;
      int sx = d->miniW + stripe;
      draw_line(d, sx, start, sx, end, color);
    }

    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
    return 0;
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main(int argc, char **argv) {
    if (argc != 2) {
        ft_putendl_fd(ERO_USA, 2);
        return 1;
    }

    // 1) parse .cub file
    t_cub3d *cub3d = malloc(sizeof(*cub3d));
    init_cub3d(cub3d, argv[1]);
    if (parsing_manager(&cub3d) == -1)
        return 1;

    // 2) set up renderer state
    t_data d = {0};
    d.cub3d  = cub3d;
    d.mapW   = cub3d->map.map_width;
    d.mapH   = cub3d->map.map_height;
    d.scale  = 8;                         // you can tweak this
    d.miniW  = d.mapW * d.scale;
    d.viewW  = 640;                       // e.g. fixed 3D-view width
    d.winW   = d.miniW + d.viewW;
    d.winH   = d.mapH * d.scale;          // match minimap height

    // 3) init MiniLibX
    d.mlx = mlx_init();
    d.win = mlx_new_window(d.mlx, d.winW, d.winH, "cub3d");
    d.img = mlx_new_image(d.mlx, d.winW, d.winH);
    d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);

    // 4) player start
    //    find 'N','S','E','W' in cub3d->point[y][x].access==2,
    //    set posX,posY and dirX,dirY accordingly.
    //    For brevity let's just zero them here:
    d.posX = cub3d->player.map_x + 0.5;
    d.posY = cub3d->player.map_y + 0.5;
    d.dirX = -1;  d.dirY = 0;
    d.planeX = 0; d.planeY = 0.66;

    // 5) hooks
    mlx_hook(d.win, 2, 1<<0, key_press,   &d);
    mlx_hook(d.win, 3, 1<<1, key_release, &d);
    mlx_loop_hook(d.mlx, render_frame,    &d);

    // 6) run
    mlx_loop(d.mlx);

    return 0;
}
