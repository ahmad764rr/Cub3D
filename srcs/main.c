// raycaster.c
// Full merged cub3d + raycasting + minimap engine


#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../includes/cub3d.h"
// Keycodes for X11
#define KEY_ESC    65307
#define KEY_W      119
#define KEY_S      115
#define KEY_A      97
#define KEY_D      100
#define KEY_LEFT   65361
#define KEY_RIGHT  65363
#define KEY_UP     65362
#define KEY_DOWN   65364

typedef struct s_data {
    void      *mlx;
    void      *win;
    void      *img;
    char      *addr;
    int        bpp;
    int        line_len;
    int        endian;

    double     posX, posY;
    double     dirX, dirY;
    double     planeX, planeY;

    int        keys[65536];

    t_cub3d   *cub3d;      // parsed map & textures
    int        mapW, mapH; // map dimensions
    int        scale;      // pixel size per map cell
    int        miniW;      // minimap width in px
    int        viewW;      // 3D view width
    int        winW, winH; // total window size
} t_data;

// ─── Pixel Helpers ─────────────────────────────────────────────────────────────

static void put_pixel(t_data *d, int x, int y, int color) {
    if (x < 0 || x >= d->winW || y < 0 || y >= d->winH) return;
    char *dst = d->addr + (y * d->line_len + x * (d->bpp/8));
    *(unsigned int*)dst = color;
}

static void draw_rect(t_data *d, int x, int y, int w, int h, int color) {
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j)
            put_pixel(d, x + i, y + j, color);
}

static void draw_line(t_data *d, int x0, int y0, int x1, int y1, int col) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    while (1) {
        put_pixel(d, x0, y0, col);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

// ─── Input Handling ────────────────────────────────────────────────────────────

static int key_press(int kc, t_data *d) {
    if (kc == KEY_ESC)
        exit(0);
    d->keys[kc] = 1;
    return 0;
}

static int key_release(int kc, t_data *d) {
    d->keys[kc] = 0;
    return 0;
}

// ─── Player Movement ───────────────────────────────────────────────────────────

static void move_player(t_data *d, double dt) {
    double ms = dt * 5.0;
    double rs = dt * 3.0;

    // forward/back
    if (d->keys[KEY_W] || d->keys[KEY_UP]) {
        if (d->cub3d->point[(int)d->posY][(int)(d->posX + d->dirX * ms)].access == 0)
            d->posX += d->dirX * ms;
        if (d->cub3d->point[(int)(d->posY + d->dirY * ms)][(int)d->posX].access == 0)
            d->posY += d->dirY * ms;
    }
    if (d->keys[KEY_S] || d->keys[KEY_DOWN]) {
        if (d->cub3d->point[(int)d->posY][(int)(d->posX - d->dirX * ms)].access == 0)
            d->posX -= d->dirX * ms;
        if (d->cub3d->point[(int)(d->posY - d->dirY * ms)][(int)d->posX].access == 0)
            d->posY -= d->dirY * ms;
    }

    // strafe
    if (d->keys[KEY_A] || d->keys[KEY_D]) {
        double factor = d->keys[KEY_A] ?  1 : -1;
        double sx     = factor * d->dirY * ms;
        double sy     = factor * -d->dirX * ms;
        if (d->cub3d->point[(int)d->posY][(int)(d->posX + sx)].access == 0)
            d->posX += sx;
        if (d->cub3d->point[(int)(d->posY + sy)][(int)d->posX].access == 0)
            d->posY += sy;
    }

    // rotate
    if (d->keys[KEY_LEFT] || d->keys[KEY_RIGHT]) {
        double ang = (d->keys[KEY_RIGHT] ? -rs : rs);
        double odx = d->dirX, opx = d->planeX;
        d->dirX   = odx * cos(ang) - d->dirY * sin(ang);
        d->dirY   = odx * sin(ang) + d->dirY * cos(ang);
        d->planeX = opx * cos(ang) - d->planeY * sin(ang);
        d->planeY = opx * sin(ang) + d->planeY * cos(ang);
    }
}

// ─── Render Loop ───────────────────────────────────────────────────────────────

static int render_frame(void *param) {
    t_data *d = param;
    static double last = 0;
    double now = (double)clock() / CLOCKS_PER_SEC;
    double dt  = now - last;
    last = now;

    move_player(d, dt);

    // 1) 2D minimap
    for (int y = 0; y < d->mapH; y++) {
        for (int x = 0; x < d->mapW; x++) {
            int acc = d->cub3d->point[y][x].access;
            int col = acc ? 0x777777 : 0x222222;
            draw_rect(d, x * d->scale, y * d->scale, d->scale, d->scale, col);
        }
    }
    // player dot
    int px = d->posX * d->scale;
    int py = d->posY * d->scale;
    draw_rect(d, px - 2, py - 2, 4, 4, 0x00FF00);

    // 2) sky & floor
    for (int y = 0; y < d->winH / 2; y++)
        for (int x = d->miniW; x < d->winW; x++)
            put_pixel(d, x, y, 0x87CEEB);
    for (int y = d->winH / 2; y < d->winH; y++)
        for (int x = d->miniW; x < d->winW; x++)
            put_pixel(d, x, y, 0x888888);

    // 3) raycast columns
    for (int col = 0; col < d->viewW; col++) {
        double camX = 2 * col / (double)d->viewW - 1;
        double rayX = d->dirX + d->planeX * camX;
        double rayY = d->dirY + d->planeY * camX;

        int mapX = (int)d->posX;
        int mapY = (int)d->posY;
        double dX = fabs(rayX) < 1e-6 ? 1e30 : fabs(1 / rayX);
        double dY = fabs(rayY) < 1e-6 ? 1e30 : fabs(1 / rayY);

        int stepX = rayX < 0 ? -1 : 1;
        int stepY = rayY < 0 ? -1 : 1;
        double sX = (rayX < 0
                     ? (d->posX - mapX) * dX
                     : (mapX + 1 - d->posX) * dX);
        double sY = (rayY < 0
                     ? (d->posY - mapY) * dY
                     : (mapY + 1 - d->posY) * dY);

        int hit = 0, side = 0;
        while (!hit) {
            if (sX < sY) {
                sX += dX;
                mapX += stepX;
                side = 0;
            } else {
                sY += dY;
                mapY += stepY;
                side = 1;
            }
            if (d->cub3d->point[mapY][mapX].access > 0)
                hit = 1;
        }

        double perp = (side == 0 ? (sX - dX) : (sY - dY));

        // minimap ray
        double hx = d->posX + rayX * perp;
        double hy = d->posY + rayY * perp;
        draw_line(d, px, py,
                  hx * d->scale,
                  hy * d->scale,
                  0xFF0000);

        // slice
        int h = (int)(d->winH / perp);
        int start = -h/2 + d->winH/2;
        int end   =  h/2 + d->winH/2;
        if (start < 0)      start = 0;
        if (end   >= d->winH) end = d->winH - 1;

        int color = 0xFFFFFF / d->cub3d->point[mapY][mapX].access;
        if (side) color >>= 1;
        int sx = d->miniW + col;
        draw_line(d, sx, start, sx, end, color);
    }

    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
    return 0;
}

// ─── Main ─────────────────────────────────────────────────────────────────────


#define VIEW_W 640   // 3D view width
#define WIN_H  480   // fixed window height

int main(int argc, char **argv)
{
    if (argc != 2) {
        ft_putendl_fd(ERO_USA, 2);
        return 1;
    }

    // Allocate and initialize cub3d struct
    t_cub3d *cub3d = malloc(sizeof(*cub3d));
    if (!cub3d) return 1;
    init_cub3d(cub3d, argv[1]);

    // Parse .cub file (textures, map, colors, etc.)
    if (parsing_manager(&cub3d) == -1)
        return 1;

    // Setup rendering data
    t_data d = {0};
    d.cub3d = cub3d;
    d.mapW  = cub3d->map.map_width;
    d.mapH  = cub3d->map.map_height;

    // Dynamically scale minimap to fit fixed height
    d.scale = WIN_H / d.mapH;
    if (d.scale < 1) d.scale = 1;   // at least 1px per cell

    d.miniW = d.mapW * d.scale;
    d.viewW = VIEW_W;
    d.winW  = d.miniW + d.viewW;
    d.winH  = WIN_H;
d.winW  = 800;
d.winH  = 600;
d.miniW = 200;  // fixed minimap width
d.scale = d.miniW / d.mapW;  // adjust scale to fit
d.viewW = d.winW - d.miniW;

    // Initialize MiniLibX
    d.mlx  = mlx_init();
    if (!d.mlx) { handle_error(ERO_MLX_INIT); return 1; }

    d.win  = mlx_new_window(d.mlx, d.winW, d.winH, "cub3d");
    if (!d.win) { handle_error(ERO_MLX_WIN); return 1; }

    d.img  = mlx_new_image(d.mlx, d.winW, d.winH);
    if (!d.img) { handle_error(ERO_MLX_IMG); return 1; }

    d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);
    if (!d.addr) { handle_error(ERO_MLX_ADDR); return 1; }

    // Player starting position
    d.posX   = cub3d->player.map_x + 0.5;
    d.posY   = cub3d->player.map_y + 0.5;
    d.dirX   = -1;
    d.dirY   = 0;
    d.planeX = 0;
    d.planeY = 0.66;

    // Hook input & rendering
    mlx_hook(d.win, 2, 1<<0, key_press,   &d);
    mlx_hook(d.win, 3, 1<<1, key_release, &d);
    mlx_loop_hook(d.mlx, render_frame,    &d);

    // Start main loop
    mlx_loop(d.mlx);

    // Cleanup on exit (if ever reached)
    free_texture(cub3d);
    free_map_points(cub3d);
    free(cub3d);
    return 0;
}