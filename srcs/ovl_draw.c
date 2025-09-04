/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:17:48 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:48:11 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	draw_rect(t_data *d, int xywh[], unsigned int c)
{
	int	xx;
	int	yy;
	int	x1;
	int	y1;

	if (xywh[2] <= 0 || xywh[3] <= 0)
		return ;
	x1 = xywh[0] + xywh[2];
	y1 = xywh[1] + xywh[3];
	if (xywh[0] < 0)
		xywh[0] = 0;
	if (xywh[1] < 0)
		xywh[1] = 0;
	if (x1 > d->win_w)
		x1 = d->win_w;
	if (y1 > d->win_h)
		y1 = d->win_h;
	yy = xywh[1] - 1;
	while (++yy < y1)
	{
		xx = xywh[0] - 1;
		while (++xx < x1)
			put_pixel(d, xx, yy, c);
	}
}

void	draw_rect_blend(t_data *d, int xywh[], unsigned int c, double a)
{
	int	xx_yy[2];
	int	x1;
	int	y1;

	if (xywh[2] <= 0 || xywh[3] <= 0)
		return ;
	x1 = xywh[0] + xywh[2];
	y1 = xywh[1] + xywh[3];
	if (xywh[0] < 0)
		xywh[0] = 0;
	if (xywh[1] < 0)
		xywh[1] = 0;
	if (x1 > d->win_w)
		x1 = d->win_w;
	if (y1 > d->win_h)
		y1 = d->win_h;
	xx_yy[1] = xywh[1] - 1;
	while (++xx_yy[1] < y1)
	{
		xx_yy[0] = xywh[0] - 1;
		while (++xx_yy[0] < x1)
			put_pixel_blend(d, xx_yy, c, a);
	}
}

void	set_data_draw_line(int xy01[], int dsxy[], int x01, int y01[])
{
	xy01[0] = x01;
	xy01[1] = y01[0];
	xy01[2] = x01;
	xy01[3] = y01[1];
	dsxy[0] = abs(xy01[2] - xy01[0]);
	dsxy[1] = -abs(xy01[3] - xy01[1]);
	dsxy[2] = (xy01[0] < xy01[2]);
	dsxy[3] = (xy01[1] < xy01[3]);
}

void	check_data_draw_line(int dsxy[], int *err)
{
	if (!dsxy[2])
		dsxy[2] = -1;
	if (!dsxy[3])
		dsxy[3] = -1;
	*err = dsxy[0] + dsxy[1];
}

void	draw_line(t_data *d, int x01, int y01[], unsigned int c)
{
	int	dsxy[4];
	int	xy01[4];
	int	err;
	int	e2;

	set_data_draw_line(xy01, dsxy, x01, y01);
	check_data_draw_line(dsxy, &err);
	while (1)
	{
		put_pixel(d, xy01[0], xy01[1], c);
		if (xy01[0] == xy01[2] && xy01[1] == xy01[3])
			break ;
		e2 = 2 * err;
		if (e2 >= dsxy[1])
		{
			err += dsxy[1];
			xy01[0] += dsxy[2];
		}
		if (e2 <= dsxy[0])
		{
			err += dsxy[0];
			xy01[1] += dsxy[3];
		}
	}
}
