/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/03 14:10:49 by ahramada         ###   ########.fr       */
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
	unsigned int	dr;
	unsigned int	dg;
	unsigned int	db;
	unsigned int	sr;
	unsigned int	sg;
	unsigned int	sb;

	dr = (dst >> 16) & 0xFF;
	dg = (dst >> 8) & 0xFF;
	db = dst & 0xFF;
	sr = (src >> 16) & 0xFF;
	sg = (src >> 8) & 0xFF;
	sb = src & 0xFF;
	dr = (unsigned int)(sr * a + dr * (1.0 - a));
	dg = (unsigned int)(sg * a + dg * (1.0 - a));
	db = (unsigned int)(sb * a + db * (1.0 - a));
	return ((dr << 16) | (dg << 8) | db);
}

void	put_pixel_blend(t_data *d, int x, int y,
	unsigned int color, double a)
{
	unsigned int	dst;
	unsigned int	out;

	if ((unsigned)x >= (unsigned)d->win_w
		|| (unsigned)y >= (unsigned)d->win_h)
		return ;
	dst = get_pixel(d, x, y);
	out = blend_rgb(dst, color, a);
	put_pixel(d, x, y, out);
}