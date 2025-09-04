/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_sky.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:13:13 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	draw_sky_floor(t_data *d)
{
	int	hz;
	int	x;
	int	y;

	hz = d->win_h / 2 + d->pitch;
	if (hz < 0)
		hz = 0;
	if (hz > d->win_h)
		hz = d->win_h;
	y = -1;
	while (++y < hz)
	{
		x = -1;
		while (++x < d->win_w)
			put_pixel(d, x, y, 0x87CEEB);
	}
	while (y < d->win_h)
	{
		x = -1;
		while (++x < d->win_w)
			put_pixel(d, x, y, 0x888888);
		++y;
	}
}
