/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:52:49 by nqasem           ###   ########.fr       */
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
	int				rxywh[4];
	unsigned int	col;

	y = -1;
	rxywh[2] = d->mm_scale;
	rxywh[3] = d->mm_scale;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			set_cell_color(d->c3d->point[y][x].access, &col);
			rxywh[0] = d->mm_x + x * d->mm_scale;
			rxywh[1] = d->mm_y + y * d->mm_scale;
			draw_rect_blend(d, rxywh, col, MINI_CELL_A);
		}
	}
}

void	mm_draw_player_and_head(t_data *d, int *px, int *py)
{
	int	phxy[4];
	int	xywh[4];

	*px = d->mm_x + (int)(d->pos_x * d->mm_scale);
	*py = d->mm_y + (int)(d->pos_y * d->mm_scale);
	xywh[0] = *px - MINI_DOT_SZ / 2;
	xywh[1] = *py - MINI_DOT_SZ / 2;
	xywh[2] = MINI_DOT_SZ;
	xywh[3] = MINI_DOT_SZ;
	draw_rect(d, xywh, 0x00FF00);
	phxy[2] = *px + (int)(d->dir_x * MINI_HEADLEN);
	phxy[3] = *py + (int)(d->dir_y * MINI_HEADLEN);
	phxy[0] = *px;
	phxy[1] = *py;
	draw_line_clip(d, phxy, 0x00FF00);
}
