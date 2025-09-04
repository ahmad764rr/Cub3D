/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/04 13:04:40 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	mm_compute_rect(t_data *d)
{
	int	sx;
	int	sy;
	int	sc;

	if (d->map_w > 0)
		sx = MINI_MAX_W / d->map_w;
	else
		sx = MINI_MAX_W;
	if (d->map_h > 0)
		sy = MINI_MAX_H / d->map_h;
	else
		sy = MINI_MAX_H;
	if (sx < sy)
		sc = sx;
	else
		sc = sy;
	if (sc < 1)
		sc = 1;
	d->mm_scale = sc;
	d->mm_w = d->map_w * sc;
	d->mm_h = d->map_h * sc;
	d->mm_x = MINI_PAD;
	d->mm_y = MINI_PAD;
}

static void	set_cell_color(int acc, unsigned int *col)
{
	if (acc)
		*col = 0x7A7A7A;
	else
		*col = 0x2A2A2A;
}

void	mm_draw_cells(t_data *d)
{
	int				y;
	int				x;
	int				rx;
	int				ry;
	unsigned int	col;

	y = -1;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			set_cell_color(d->c3d->point[y][x].access, &col);
			rx = d->mm_x + x * d->mm_scale;
			ry = d->mm_y + y * d->mm_scale;
			draw_rect_blend(d, rx, ry, d->mm_scale,
				d->mm_scale, col, MINI_CELL_A);
		}
	}
}

void	mm_draw_player_and_head(t_data *d, int *px, int *py)
{
	int phxy[4];

	*px = d->mm_x + (int)(d->pos_x * d->mm_scale);
	*py = d->mm_y + (int)(d->pos_y * d->mm_scale);
	draw_rect(d, *px - MINI_DOT_SZ / 2, *py - MINI_DOT_SZ / 2,
		MINI_DOT_SZ, MINI_DOT_SZ, 0x00FF00);
	phxy[2] = *px + (int)(d->dir_x * MINI_HEADLEN);
	phxy[3] = *py + (int)(d->dir_y * MINI_HEADLEN);
	phxy[0] = *px;
	phxy[1] = *py;
	draw_line_clip(d, phxy, 0x00FF00);
}

void	mm_draw_rays(t_data *d, int px, int py)
{
	int ptxy[4];
	int	col;

	ptxy[0] = px;
	ptxy[1] = py;
	col = 0;
	while (col < d->win_w)
	{
		ptxy[2] = d->mm_x + (int)(d->hit_x[col] * d->mm_scale);
		ptxy[3] = d->mm_y + (int)(d->hit_y[col] * d->mm_scale);
		draw_line_clip(d, ptxy, MINI_RAY_COL);
		col += MINI_RAY_STEP;
	}
}

void	mm_draw_border(t_data *d)
{
	int	x;
	int	y;

	x = d->mm_x - 2;
	while (x < d->mm_x + d->mm_w + 2)
	{
		put_pixel(d, x, d->mm_y - 2, 0xFFFFFF);
		put_pixel(d, x, d->mm_y + d->mm_h + 1, 0xFFFFFF);
		x++;
	}
	y = d->mm_y - 2;
	while (y < d->mm_y + d->mm_h + 2)
	{
		put_pixel(d, d->mm_x - 2, y, 0xFFFFFF);
		put_pixel(d, d->mm_x + d->mm_w + 1, y, 0xFFFFFF);
		y++;
	}
}

void	draw_minimap_overlay(t_data *d)
{
	int	px;
	int	py;

	draw_rect_blend(d, d->mm_x - 2, d->mm_y - 2,
		d->mm_w + 4, d->mm_h + 4, 0x000000, MINI_BG_A);
	mm_draw_cells(d);
	mm_draw_player_and_head(d, &px, &py);
	mm_draw_rays(d, px, py);
	mm_draw_border(d);
}
