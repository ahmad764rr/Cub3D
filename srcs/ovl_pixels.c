/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/10 22:38:46 by ahramada         ###   ########.fr       */
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

unsigned int	tex_get_pixel(t_tex *t, int x, int y)
{
	char	*src;

	if (!t || !t->addr)
		return (0);
	if ((unsigned)x >= (unsigned)t->width)
		return (0);
	if ((unsigned)y >= (unsigned)t->height)
		return (0);
	src = t->addr + (y * t->line_len + x * (t->bpp / 8));
	return (*(unsigned int *)src);
}
