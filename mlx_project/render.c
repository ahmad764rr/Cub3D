#include "render.h"
#include <stdlib.h>

// put a pixel into the MLX image buffer
void put_pixel(t_data *d, int x, int y, int c) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    char *dst = d->addr + (y * d->line + x * (d->bpp / 8));
    *(unsigned int*)dst = c;
}

// draw one centered TILE-sized box at grid cell (tx,ty)
void draw_tile(t_data *d, int tx, int ty, int c) {
    int x0 = tx * GRID + (GRID - TILE) / 2;
    int y0 = ty * GRID + (GRID - TILE) / 2;
    for (int yy = 0; yy < TILE; yy++)
        for (int xx = 0; xx < TILE; xx++)
            put_pixel(d, x0 + xx, y0 + yy, c);
}

// draw the entire map
void draw_map(t_data *d) {
    for (int j = 0; j < MAP_H; j++)
        for (int i = 0; i < MAP_W; i++) {
            int t = d->map[j * MAP_W + i];
            draw_tile(d, i, j, t ? WALL : FLOOR);
        }
}

// draw grid lines
void draw_grid(t_data *d) {
    // horizontal
    for (int y = 0; y <= MAP_H; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(d, x, y * GRID, GRID_C);
    // vertical
    for (int x = 0; x <= MAP_W; x++)
        for (int y = 0; y < HEIGHT; y++)
            put_pixel(d, x * GRID, y, GRID_C);
}

// draw the player square
void draw_player(t_data *d) {
    int x0 = (int)d->px - P_SIZE/2;
    int y0 = (int)d->py - P_SIZE/2;
    for (int yy = 0; yy < P_SIZE; yy++)
        for (int xx = 0; xx < P_SIZE; xx++)
            put_pixel(d, x0 + xx, y0 + yy, PLAYER);
}

// draw a ray of length len in player’s facing direction
void draw_ray(t_data *d, int len, int c) {
    int x0 = (int)d->px;
    int y0 = (int)d->py;
    int x1 = x0 + (int)(d->pdx * len);
    int y1 = y0 + (int)(d->pdy * len);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(d, x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}



void draw_all(t_data *d) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            put_pixel(d, x, y, 0x000000); 
        }
    }

    draw_map(d);
    draw_grid(d);
    draw_player(d);
    draw_ray(d, GRID, RAY);
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

