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
	int dsxy[4];
	int	err;
	int	e2;

	dsxy[0] = abs(x1 - x0);
	dsxy[1] = -abs(y1 - y0);
	dsxy[2] = (x0 < x1);
	dsxy[3] = (y0 < y1);
	if (!dsxy[2])
		dsxy[2] = -1;
	if (!dsxy[3])
		dsxy[3] = -1;
	err = dsxy[0] + dsxy[1];
	while (1)
	{
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

void set_line_clip_data(int xy01_[], int dsxy[], int xy01[])
{
	xy01_[0] = xy01[0];
	xy01_[1] = xy01[1];
	xy01_[2] = xy01[2];
	xy01_[3] = xy01[3];
	dsxy[0] = abs(xy01_[2] - xy01_[0]);
	dsxy[1] = -abs(xy01_[3] - xy01_[1]);
	dsxy[2] = (xy01_[0] < xy01_[2]) ? 1 : -1;
	dsxy[3] = (xy01_[1] < xy01_[3]) ? 1 : -1;
}

void	_set_line_clip_data2(int rxywh[], int dsxy[], t_data *d, int err[])
{
	rxywh[0] = d->mm_x;
	rxywh[1] = d->mm_y;
	rxywh[2] = d->mm_w;
	rxywh[3] = d->mm_h;
	err[0] = dsxy[0] + dsxy[1];
}

void	draw_line_clip(t_data *d, int xy01[], unsigned int c)
{
	int xy01_[4];
	int dsxy[4];
	int rxywh[4];
	int	err_e2[2];

	set_line_clip_data(xy01_, dsxy, xy01);
	_set_line_clip_data2(rxywh, dsxy, d, err_e2);
	while (1)
	{
		if (xy01_[0] >= rxywh[0] && xy01_[0] < rxywh[0] + rxywh[2] && xy01_[1] >= rxywh[1] && xy01_[1] < rxywh[1] + rxywh[3])
			put_pixel(d, xy01_[0], xy01_[1], c);
		if (xy01_[0] == xy01_[2] && xy01_[1] == xy01_[3])
			break ;
		err_e2[1] = 2 * err_e2[0];
		if (err_e2[1] >= dsxy[1])
		{
			err_e2[0] += dsxy[1];
			xy01_[0] += dsxy[2];
		}
		if (err_e2[1] <= dsxy[0])
		{
			err_e2[0] += dsxy[0];
			xy01_[1] += dsxy[3];
		}
	}
}
