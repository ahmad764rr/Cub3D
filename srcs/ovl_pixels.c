/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:25:28 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	put_pixel(t_data *d, int x, int y, unsigned int color)
{
	char	*dst;

	if ((unsigned)x >= (unsigned)d->win_w)
		return ;
	if ((unsigned)y >= (unsigned)d->win_h)
		return ;
	dst = d->addr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_data *d, int x, int y)
{
	char	*src;

	if ((unsigned)x >= (unsigned)d->win_w)
		return (0);
	if ((unsigned)y >= (unsigned)d->win_h)
		return (0);
	src = d->addr + (y * d->line_len + x * (d->bpp / 8));
	return (*(unsigned int *)src);
}

unsigned int	blend_rgb(unsigned int dst, unsigned int src,
	double a)
{
	unsigned int	drgb[3];
	unsigned int	srgb[3];

	drgb[0] = (dst >> 16) & 0xFF;
	drgb[1] = (dst >> 8) & 0xFF;
	drgb[2] = dst & 0xFF;
	srgb[0] = (src >> 16) & 0xFF;
	srgb[1] = (src >> 8) & 0xFF;
	srgb[2] = src & 0xFF;
	drgb[0] = (unsigned int)(srgb[0] * a + drgb[0] * (1.0 - a));
	drgb[1] = (unsigned int)(srgb[1] * a + drgb[1] * (1.0 - a));
	drgb[2] = (unsigned int)(srgb[2] * a + drgb[2] * (1.0 - a));
	return ((drgb[0] << 16) | (drgb[1] << 8) | drgb[2]);
}

void	put_pixel_blend(t_data *d, int xy[],
	unsigned int color, double a)
{
	unsigned int	dst;
	unsigned int	out;

	if ((unsigned)xy[0] >= (unsigned)d->win_w
		|| (unsigned)xy[1] >= (unsigned)d->win_h)
		return ;
	dst = get_pixel(d, xy[0], xy[1]);
	out = blend_rgb(dst, color, a);
	put_pixel(d, xy[0], xy[1], out);
}
