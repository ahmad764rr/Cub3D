/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_minimap2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:50:33 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:56:01 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	mm_draw_rays(t_data *d, int px, int py)
{
	int	ptxy[4];
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
	int	xywh[4];
	int	px;
	int	py;

	xywh[0] = d->mm_x - 2;
	xywh[1] = d->mm_y - 2;
	xywh[2] = d->mm_w + 4;
	xywh[3] = d->mm_h + 4;
	draw_rect_blend(d, xywh, 0x000000, MINI_BG_A);
	mm_draw_cells(d);
	mm_draw_player_and_head(d, &px, &py);
	mm_draw_rays(d, px, py);
	mm_draw_border(d);
}
