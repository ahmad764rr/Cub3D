/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/10 13:41:02 by ahramada         ###   ########.fr       */
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
