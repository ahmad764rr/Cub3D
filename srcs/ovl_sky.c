/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_sky.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/15 16:11:51 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_ceiling(t_data *d, int hz, unsigned int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < hz)
	{
		x = -1;
		while (++x < d->win_w)
			put_pixel(d, x, y, color);
	}
}

static void	draw_floor(t_data *d, int hz, unsigned int color)
{
	int	x;
	int	y;

	y = hz - 1;
	while (++y < d->win_h)
	{
		x = -1;
		while (++x < d->win_w)
			put_pixel(d, x, y, color);
	}
}

void	draw_sky_floor(t_data *d)
{
	int				hz;
	unsigned int	ceil_col;
	unsigned int	floor_col;

	hz = d->win_h / 2;
	if (hz < 0)
		hz = 0;
	if (hz > d->win_h)
		hz = d->win_h;
	ceil_col = (d->c3d->map.color_ceiling.r << 16)
		| (d->c3d->map.color_ceiling.g << 8)
		| (d->c3d->map.color_ceiling.b);
	floor_col = (d->c3d->map.color_floor.r << 16)
		| (d->c3d->map.color_floor.g << 8)
		| (d->c3d->map.color_floor.b);
	draw_ceiling(d, hz, ceil_col);
	draw_floor(d, hz, floor_col);
}
