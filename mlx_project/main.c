// main.c
#include "render.h"
#include <stdlib.h>

static int keys[65536] = {0};
int map_data[MAP_W * MAP_H] = {
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

int key_press(int keycode, int *keys) {
    keys[keycode] = 1;
    return 0;
}

int key_release(int keycode, int *keys) {
    keys[keycode] = 0;
    return 0;
}

int handle_key(int keycode, t_data *d) {
    const float move_speed = 2.0f;
    const float rot_speed = 0.1f;
    if (keycode == 65307)
        exit(0);
    if (keycode == 'w') {
        d->px += d->pdx * move_speed;
        d->py += d->pdy * move_speed;
    }
    if (keycode == 's') {
        d->px -= d->pdx * move_speed;
        d->py -= d->pdy * move_speed;
    }
    if (keycode == 'a') {
        d->pa -= rot_speed;
        if (d->pa < 0) d->pa += 2 * PI;
        d->pdx = cos(d->pa);
        d->pdy = sin(d->pa);
    }
    if (keycode == 'd') {
        d->pa += rot_speed;
        if (d->pa > 2 * PI) d->pa -= 2 * PI;
        d->pdx = cos(d->pa);
        d->pdy = sin(d->pa);
    }
    draw_all(d);
    return 0;
}
int update(t_data *d) {
    const float move_speed = 0.01f;
    const float rot_speed = 0.001f;

    if (keys['w']) {
        d->px += d->pdx * move_speed;
        d->py += d->pdy * move_speed;
    }
    if (keys['s']) {
        d->px -= d->pdx * move_speed;
        d->py -= d->pdy * move_speed;
    }
    if (keys['a']) {
        d->pa -= rot_speed;
        if (d->pa < 0) d->pa += 2 * PI;
        d->pdx = cos(d->pa) * 5;
        d->pdy = sin(d->pa) * 5;
    }
    if (keys['d']) {
        d->pa += rot_speed;
        if (d->pa > 2 * PI) d->pa -= 2 * PI;
        d->pdx = cos(d->pa) * 5;
        d->pdy = sin(d->pa) * 5;
    }

    if (keys[65307]) // ESC
        exit(0);

    draw_all(d);
    return 0;
}

int main(void) {
    t_data d;
    d.mlx = mlx_init();
    d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "Grid with Walls and Player");
    d.img = mlx_new_image(d.mlx, WIDTH, HEIGHT);
    d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.line, &d.endian);
    for (int i = 0; i < MAP_W * MAP_H; i++)
	    d.map[i] = map_data[i];
	d.px = 2 * GRID + GRID / 2;
	d.py = 2 * GRID + GRID / 2;
	d.pa = 0;
	d.pdx = cos(d.pa);
	d.pdy = sin(d.pa);
	mlx_hook(d.win, 2, 1L << 0, (void*)key_press, keys);
    mlx_hook(d.win, 3, 1L << 1, (void*)key_release, keys);
    //mlx_key_hook(d.win, handle_key, &d);
	mlx_loop_hook(d.mlx, update, &d);
    draw_all(&d);
    mlx_loop(d.mlx);

    return 0;
}