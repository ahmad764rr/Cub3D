#include "render.h"
#include <stdlib.h>


void draw_ray(t_data *d, float x0f, float y0f, float x1f, float y1f, int color) {
    int x0 = (int)roundf(x0f);
    int y0 = (int)roundf(y0f);
    int x1 = (int)roundf(x1f);
    int y1 = (int)roundf(y1f);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    int steps = 0, max_steps = dx + dy + 1;  // a safe upper bound

    while (steps++ < max_steps) {
        put_pixel(d, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}




float degToRad(int a) { return a * M_PI / 180.0; }
int FixAng(int a) { if (a > 359) { a -= 360; } if (a < 0) { a += 360; } return a; }
float distance(float ax, float ay, float bx, float by, float ang) {
    return cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay);
}

#define FOV 60
#define NUM_RAYS 60

void drawRays3D(t_data *d)
{
    float pa_deg = d->pa * (-180.0f / M_PI); // convert player angle to degrees
    float ra = FixAng(pa_deg + FOV / 2);    // start ray angle from left side of FOV

    for (int r = 0; r < NUM_RAYS; r++)
    {
        float ra_rad = degToRad(ra); // convert current ray angle to radians
        float Tan = tanf(ra_rad);
        float rx, ry, xo, yo;
        float disV = 1e6, disH = 1e6;
        float vx = d->px, vy = d->py, hx = d->px, hy = d->py;
        int dof, mx, my, mp;

        // --- VERTICAL ---
        dof = 0;
        if (cosf(ra_rad) > 0.001f) {
            rx = ((int)(d->px / GRID) * GRID) + GRID;
            ry = (d->px - rx) * Tan + d->py;
            xo = GRID;
            yo = -xo * Tan;
        }
        else if (cosf(ra_rad) < -0.001f) {
            rx = ((int)(d->px / GRID) * GRID) - 0.0001f;
            ry = (d->px - rx) * Tan + d->py;
            xo = -GRID;
            yo = -xo * Tan;
        }
        else {
            rx = d->px;
            ry = d->py;
            dof = MAP_W;
        }

        while (dof < MAP_W) {
            mx = (int)(rx / GRID);
            my = (int)(ry / GRID);
            if (mx >= 0 && mx < MAP_W && my >= 0 && my < MAP_H) {
                mp = my * MAP_W + mx;
                if (d->map[mp] == 1) {
                    vx = rx; vy = ry;
                    disV = distance(d->px, d->py, vx, vy, ra);
                    break;
                }
            } else break;
            rx += xo; ry += yo; dof++;
        }

        // --- HORIZONTAL ---
        Tan = 1.0f / Tan;
        dof = 0;
        if (sinf(ra_rad) > 0.001f) {
            ry = ((int)(d->py / GRID) * GRID) - 0.0001f;
            rx = (d->py - ry) * Tan + d->px;
            yo = -GRID;
            xo = -yo * Tan;
        }
        else if (sinf(ra_rad) < -0.001f) {
            ry = ((int)(d->py / GRID) * GRID) + GRID;
            rx = (d->py - ry) * Tan + d->px;
            yo = GRID;
            xo = -yo * Tan;
        }
        else {
            rx = d->px;
            ry = d->py;
            dof = MAP_H;
        }

        while (dof < MAP_H) {
            mx = (int)(rx / GRID);
            my = (int)(ry / GRID);
            if (mx >= 0 && mx < MAP_W && my >= 0 && my < MAP_H) {
                mp = my * MAP_W + mx;
                if (d->map[mp] == 1) {
                    hx = rx; hy = ry;
                    disH = distance(d->px, d->py, hx, hy, ra);
                    break;
                }
            } else break;
            rx += xo; ry += yo; dof++;
        }

        // draw the ray to the closest hit
        if (disV < disH)
            draw_ray(d, d->px, d->py, vx, vy, RAY);
        else
            draw_ray(d, d->px, d->py, hx, hy, RAY);

        // move to next ray angle
        ra = FixAng(ra - (FOV / (float)NUM_RAYS));
    }
}




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
void draw_looking(t_data *d, int len, int c) {
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
	drawRays3D(d);
    draw_looking(d, LINE_LENGTH, PLAYER);
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

