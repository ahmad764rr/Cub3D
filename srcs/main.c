// main.c
// cub3d + raycasting + minimap + (WSL-proof) keyboard handling

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../includes/cub3d.h"   // must (directly or indirectly) include mlx.h

// ─── Cross-platform key helpers (Linux hw keycode | Linux KeySym | mac keycode)
static int is_key_w(int kc)     { return kc == 25  || kc == 119 || kc == 13; }   // W
static int is_key_s(int kc)     { return kc == 39  || kc == 115 || kc == 1;  }   // S
static int is_key_a(int kc)     { return kc == 38  || kc == 97  || kc == 0;  }   // A
static int is_key_d(int kc)     { return kc == 40  || kc == 100 || kc == 2;  }   // D
static int is_key_left(int kc)  { return kc == 113 || kc == 65361 || kc == 123; } // ←
static int is_key_right(int kc) { return kc == 114 || kc == 65363 || kc == 124; } // →
static int is_key_up(int kc)    { return kc == 111 || kc == 65362 || kc == 126; } // ↑
static int is_key_down(int kc)  { return kc == 116 || kc == 65364 || kc == 125; } // ↓
static int is_key_esc(int kc)   { return kc == 65307 || kc == 53; }               // ESC
// optional: pitch look keys
static int is_key_r(int kc)     { return kc == 27  || kc == 114 || kc == 15; }    // R
static int is_key_f(int kc)     { return kc == 41  || kc == 102 || kc == 3;  }    // F

typedef struct s_data {
    void      *mlx, *win, *img;
    char      *addr;
    int        bpp, line_len, endian;

    double     posX, posY;      // player position (map units)
    double     dirX, dirY;      // facing direction (unit)
    double     planeX, planeY;  // camera plane

    // action flags (decoupled from raw keycodes)
    int        act_forward, act_back, act_left, act_right, act_turn_l, act_turn_r;
    int        look_up, look_down; // optional pitch controls

    int        pitch;           // vertical shift of horizon (+down, -up)

    t_cub3d   *cub3d;
    int        mapW, mapH;
    int        scale;           // px per cell for minimap (>=1)
    int        miniW;           // minimap width (px)
    int        viewW;           // 3D view width (px)
    int        winW, winH;      // total window size
} t_data;

// ─── Pixels & drawing helpers ─────────────────────────────────────────────────
static inline void put_pixel(t_data *d, int x, int y, int color) {
    if ((unsigned)x >= (unsigned)d->winW || (unsigned)y >= (unsigned)d->winH) return;
    char *dst = d->addr + (y * d->line_len + x * (d->bpp/8));
    *(unsigned int*)dst = (unsigned int)color;
}

static void draw_rect(t_data *d, int x, int y, int w, int h, int color) {
    if (w <= 0 || h <= 0) return;
    int x1 = x + w, y1 = y + h;
    if (x < 0) x = 0; if (y < 0) y = 0;
    if (x1 > d->winW) x1 = d->winW;
    if (y1 > d->winH) y1 = d->winH;
    for (int yy = y; yy < y1; ++yy)
        for (int xx = x; xx < x1; ++xx)
            put_pixel(d, xx, yy, color);
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

// ─── Input (WSL-safe) ────────────────────────────────────────────────────────
static int key_press(int kc, t_data *d) {
    if (is_key_esc(kc)) exit(0);

    if (is_key_w(kc) || is_key_up(kc))   d->act_forward = 1;
    if (is_key_s(kc) || is_key_down(kc)) d->act_back    = 1;
    if (is_key_a(kc))                    d->act_left    = 1;
    if (is_key_d(kc))                    d->act_right   = 1;
    if (is_key_left(kc))                 d->act_turn_l  = 1;
    if (is_key_right(kc))                d->act_turn_r  = 1;

    if (is_key_r(kc)) d->look_up   = 1;
    if (is_key_f(kc)) d->look_down = 1;

    // // debug: uncomment to see what WSL sends
    // fprintf(stderr, "press kc=%d\n", kc);
    return 0;
}

static int key_release(int kc, t_data *d) {
    if (is_key_w(kc) || is_key_up(kc))   d->act_forward = 0;
    if (is_key_s(kc) || is_key_down(kc)) d->act_back    = 0;
    if (is_key_a(kc))                    d->act_left    = 0;
    if (is_key_d(kc))                    d->act_right   = 0;
    if (is_key_left(kc))                 d->act_turn_l  = 0;
    if (is_key_right(kc))                d->act_turn_r  = 0;

    if (is_key_r(kc)) d->look_up   = 0;
    if (is_key_f(kc)) d->look_down = 0;

    // fprintf(stderr, "release kc=%d\n", kc);
    return 0;
}

static int close_game(t_data *d) {
    (void)d;
    exit(0);
    return 0;
}

// ─── Movement & camera ────────────────────────────────────────────────────────
static void move_player(t_data *d, double dt) {
    const double ms = dt * 5.0;  // move speed
    const double rs = dt * 3.0;  // rot speed

    // forward/back
    if (d->act_forward) {
        double nx = d->posX + d->dirX * ms;
        double ny = d->posY + d->dirY * ms;
        if (d->cub3d->point[(int)d->posY][(int)nx].access == 0) d->posX = nx;
        if (d->cub3d->point[(int)ny][(int)d->posX].access == 0) d->posY = ny;
    }
    if (d->act_back) {
        double nx = d->posX - d->dirX * ms;
        double ny = d->posY - d->dirY * ms;
        if (d->cub3d->point[(int)d->posY][(int)nx].access == 0) d->posX = nx;
        if (d->cub3d->point[(int)ny][(int)d->posX].access == 0) d->posY = ny;
    }

    // strafe
    if (d->act_left || d->act_right) {
        double side = d->act_left ? 1.0 : -1.0;
        double sx = side * d->dirY * ms;
        double sy = side * -d->dirX * ms;
        if (d->cub3d->point[(int)d->posY][(int)(d->posX + sx)].access == 0) d->posX += sx;
        if (d->cub3d->point[(int)(d->posY + sy)][(int)d->posX].access == 0) d->posY += sy;
    }

    // rotate
    if (d->act_turn_l || d->act_turn_r) {
        double ang = d->act_turn_r ? -rs : rs;
        double odx = d->dirX, opx = d->planeX;
        d->dirX   = d->dirX * cos(ang) - d->dirY * sin(ang);
        d->dirY   = odx      * sin(ang) + d->dirY * cos(ang);
        d->planeX = d->planeX * cos(ang) - d->planeY * sin(ang);
        d->planeY = opx      * sin(ang) + d->planeY * cos(ang);
    }

    // optional: look up / down with R/F
    int pitch_speed = (int)(dt * 600.0);
    if (d->look_up)   d->pitch -= pitch_speed;
    if (d->look_down) d->pitch += pitch_speed;
    int maxP = d->winH/2 - 10;
    if (d->pitch >  maxP) d->pitch =  maxP;
    if (d->pitch < -maxP) d->pitch = -maxP;
}

// ─── Render loop ──────────────────────────────────────────────────────────────
static int render_frame(void *param) {
    t_data *d = (t_data*)param;
    static double last = 0.0;
    double now = (double)clock() / CLOCKS_PER_SEC;
    double dt  = now - last;
    if (last == 0.0) dt = 0.016;
    last = now;

    move_player(d, dt);

    // minimap
    for (int y = 0; y < d->mapH; y++)
        for (int x = 0; x < d->mapW; x++) {
            int acc = d->cub3d->point[y][x].access;
            int col = acc ? 0x777777 : 0x222222;
            draw_rect(d, x * d->scale, y * d->scale, d->scale, d->scale, col);
        }
    int px = (int)(d->posX * d->scale);
    int py = (int)(d->posY * d->scale);
    draw_rect(d, px - 2, py - 2, 4, 4, 0x00FF00);

    // sky & floor with pitch
    int horizon = d->winH/2 + d->pitch;
    if (horizon < 0) horizon = 0;
    if (horizon > d->winH) horizon = d->winH;
    for (int y = 0; y < horizon; y++)
        for (int x = d->miniW; x < d->winW; x++)
            put_pixel(d, x, y, 0x87CEEB);
    for (int y = horizon; y < d->winH; y++)
        for (int x = d->miniW; x < d->winW; x++)
            put_pixel(d, x, y, 0x888888);

    // raycast
    for (int col = 0; col < d->viewW; col++) {
        double camX = 2.0 * col / (double)d->viewW - 1.0;
        double rayX = d->dirX + d->planeX * camX;
        double rayY = d->dirY + d->planeY * camX;

        int mapX = (int)d->posX, mapY = (int)d->posY;
        double dX = fabs(rayX) < 1e-9 ? 1e30 : fabs(1.0 / rayX);
        double dY = fabs(rayY) < 1e-9 ? 1e30 : fabs(1.0 / rayY);

        int stepX = (rayX < 0) ? -1 : 1;
        int stepY = (rayY < 0) ? -1 : 1;

        double sX = (rayX < 0) ? (d->posX - mapX) * dX : (mapX + 1.0 - d->posX) * dX;
        double sY = (rayY < 0) ? (d->posY - mapY) * dY : (mapY + 1.0 - d->posY) * dY;

        int hit = 0, side = 0;
        while (!hit) {
            if (sX < sY) { sX += dX; mapX += stepX; side = 0; }
            else         { sY += dY; mapY += stepY; side = 1; }
            if (mapX < 0) mapX = 0;
            if (mapY < 0) mapY = 0;
            if (mapX >= d->mapW) mapX = d->mapW - 1;
            if (mapY >= d->mapH) mapY = d->mapH - 1;
            if (d->cub3d->point[mapY][mapX].access > 0) hit = 1;
        }

        double perp = (side == 0) ? (sX - dX) : (sY - dY);

        // draw ray on minimap
        double hx = d->posX + rayX * perp;
        double hy = d->posY + rayY * perp;
        draw_line(d, px, py, (int)(hx * d->scale), (int)(hy * d->scale), 0xFF0000);

        // vertical slice (with pitch)
        int h = (int)(d->winH / perp);
        int start = -h/2 + d->winH/2 + d->pitch;
        int end   =  h/2 + d->winH/2 + d->pitch;
        if (start < 0) start = 0;
        if (end >= d->winH) end = d->winH - 1;

        int color = side ? 0x888888 : 0xBBBBBB; // placeholder (textures later)
        int sx = d->miniW + col;
        draw_line(d, sx, start, sx, end, color);
    }

    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
    return 0;
}

// ─── Main ─────────────────────────────────────────────────────────────────────
#define VIEW_W     800
#define WIN_H      600
#define WIN_W      1200
#define MINIMAP_W  400

int main(int argc, char **argv) {
    if (argc != 2) { ft_putendl_fd(ERO_USA, 2); return 1; }

    t_cub3d *cub3d = (t_cub3d*)malloc(sizeof(*cub3d));
    if (!cub3d) return 1;
    init_cub3d(cub3d, argv[1]);
    if (parsing_manager(&cub3d) == -1) return 1;

    t_data d = (t_data){0};
    d.cub3d = cub3d;
    d.mapW  = cub3d->map.map_width;
    d.mapH  = cub3d->map.map_height;

    d.winW  = WIN_W;
    d.winH  = WIN_H;
    d.miniW = MINIMAP_W;
    d.viewW = d.winW - d.miniW;

    d.scale = (d.mapW > 0) ? (d.miniW / d.mapW) : 1;
    if (d.scale < 1) d.scale = 1;

    d.pitch = 0;

    // player start
    d.posX = cub3d->player.map_x + 1.5;
    d.posY = cub3d->player.map_y + 0.5;

    // face West by default; set by spawn char later if you want
    d.dirX = -1.0; d.dirY = 0.0;
    d.planeX = 0.0; d.planeY = 0.66;

    d.mlx = mlx_init();
    if (!d.mlx) { handle_error(ERO_MLX_INIT); return 1; }
    d.win = mlx_new_window(d.mlx, d.winW, d.winH, "cub3d");
    if (!d.win) { handle_error(ERO_MLX_WIN); return 1; }
    d.img = mlx_new_image(d.mlx, d.winW, d.winH);
    if (!d.img) { handle_error(ERO_MLX_IMG); return 1; }
    d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line_len, &d.endian);
    if (!d.addr) { handle_error(ERO_MLX_ADDR); return 1; }

    mlx_hook(d.win,  2, 1<<0, key_press,   &d);   // KeyPress
    mlx_hook(d.win,  3, 1<<1, key_release, &d);   // KeyRelease
    mlx_hook(d.win, 17, 0,    close_game,  &d);   // red-cross
    mlx_loop_hook(d.mlx, render_frame,     &d);

    mlx_loop(d.mlx);

    // (usually not reached)
    free_texture(cub3d);
    free_map_points(cub3d);
    free(cub3d);
    return 0;
}
