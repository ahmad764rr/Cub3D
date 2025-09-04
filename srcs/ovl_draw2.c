/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_draw2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:45:37 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:48:17 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	set_line_clip_data(int xy01_[], int dsxy[], int xy01[])
{
	xy01_[0] = xy01[0];
	xy01_[1] = xy01[1];
	xy01_[2] = xy01[2];
	xy01_[3] = xy01[3];
	dsxy[0] = abs(xy01_[2] - xy01_[0]);
	dsxy[1] = -abs(xy01_[3] - xy01_[1]);
	if (xy01_[0] < xy01_[2])
		dsxy[2] = 1;
	else
		dsxy[2] = -1;
	if (xy01_[1] < xy01_[3])
		dsxy[3] = 1;
	else
		dsxy[3] = -1;
}

void	_set_line_clip_data2(int rxywh[], int dsxy[], t_data *d, int err[])
{
	rxywh[0] = d->mm_x;
	rxywh[1] = d->mm_y;
	rxywh[2] = d->mm_w;
	rxywh[3] = d->mm_h;
	err[0] = dsxy[0] + dsxy[1];
}

void	_condition_drawline_clip(int err_e2[], int dsxy[], int xy01_[])
{
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

void	draw_line_clip(t_data *d, int xy01[], unsigned int c)
{
	int	xy01_[4];
	int	dsxy[4];
	int	rxywh[4];
	int	err_e2[2];

	set_line_clip_data(xy01_, dsxy, xy01);
	_set_line_clip_data2(rxywh, dsxy, d, err_e2);
	while (1)
	{
		if (xy01_[0] >= rxywh[0] && xy01_[0] < rxywh[0] + rxywh[2]
			&& xy01_[1] >= rxywh[1] && xy01_[1] < rxywh[1] + rxywh[3])
			put_pixel(d, xy01_[0], xy01_[1], c);
		if (xy01_[0] == xy01_[2] && xy01_[1] == xy01_[3])
			break ;
		_condition_drawline_clip(err_e2, dsxy, xy01_);
	}
}
