#ifndef RENDER_H
#define RENDER_H

#include <mlx.h>
#include <math.h>

#define MAP_W      8
#define MAP_H      8
#define GRID       80     // full cell size
#define TILE       70     // wall-box size inside each cell
#define P_SIZE     16     // player square size
#define WIDTH   (MAP_W * GRID)
#define HEIGHT  (MAP_H * GRID)
#define PI      3.14159265359f

// colors
#define FLOOR   0x222222
#define WALL    0xFFFFFF
#define GRID_C  0x888888
#define PLAYER  0xFFFF00
#define RAY     0xFF0000

typedef struct s_data {
    void  *mlx;
    void  *win;
    void  *img;
    char  *addr;
    int    bpp;
    int    line;
    int    endian;
    int    map[MAP_W * MAP_H];
    float  px, py;    // player pos
    float  pa;        // player angle
    float  pdx, pdy;  // direction vector
} t_data;

// low-level pixel
void put_pixel(t_data *d, int x, int y, int c);

// tile/map
void draw_tile(t_data *d, int tx, int ty, int c);
void draw_map(t_data *d);

// grid
void draw_grid(t_data *d);

// player & ray
void draw_player(t_data *d);
void draw_ray(t_data *d, int len, int c);

// composite
void draw_all(t_data *d);

#endif
