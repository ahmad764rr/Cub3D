/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/03 12:41:41 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	draw_rect(t_data *d, int x, int y, int w, int h, unsigned int c)
{
	int	xx;
	int	yy;
	int	x1;
	int	y1;

	if (w <= 0 || h <= 0)
		return ;
	x1 = x + w;
	y1 = y + h;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x1 > d->win_w)
		x1 = d->win_w;
	if (y1 > d->win_h)
		y1 = d->win_h;
	yy = y - 1;
	while (++yy < y1)
	{
		xx = x - 1;
		while (++xx < x1)
			put_pixel(d, xx, yy, c);
	}
}

void	draw_rect_blend(t_data *d, int x, int y, int w, int h,
	unsigned int c, double a)
{
	int	xx;
	int	yy;
	int	x1;
	int	y1;

	if (w <= 0 || h <= 0)
		return ;
	x1 = x + w;
	y1 = y + h;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x1 > d->win_w)
		x1 = d->win_w;
	if (y1 > d->win_h)
		y1 = d->win_h;
	yy = y - 1;
	while (++yy < y1)
	{
		xx = x - 1;
		while (++xx < x1)
			put_pixel_blend(d, xx, yy, c, a);
	}
}

void	draw_line(t_data *d, int x0, int y0, int x1, int y1, unsigned int c)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1);
	sy = (y0 < y1);
	if (!sx)
		sx = -1;
	if (!sy)
		sy = -1;
	err = dx + dy;
	while (1)
	{
		put_pixel(d, x0, y0, c);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_line_clip(t_data *d, int x0, int y0, int x1, int y1,
	unsigned int c)
{
	int dsxy[4];
	int rxywh[4];
	int	err;
	int	e2;

	dsxy[0] = abs(x1 - x0);
	dsxy[1] = -abs(y1 - y0);
	dsxy[2] = (x0 < x1) ? 1 : -1;
	dsxy[3] = (y0 < y1) ? 1 : -1;
	rxywh[0] = d->mm_x;
	rxywh[1] = d->mm_y;
	rxywh[2] = d->mm_w;
	rxywh[3] = d->mm_h;
	err = dsxy[0] + dsxy[1];
	while (1)
	{
		if (x0 >= rxywh[0] && x0 < rxywh[0] + rxywh[2] && y0 >= rxywh[1] && y0 < rxywh[1] + rxywh[3])
			put_pixel(d, x0, y0, c);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dsxy[1])
		{
			err += dsxy[1];
			x0 += dsxy[2];
		}
		if (e2 <= dsxy[0])
		{
			err += dsxy[0];
			y0 += dsxy[3];
		}
	}
}