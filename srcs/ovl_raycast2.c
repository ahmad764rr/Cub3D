/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_raycast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:24 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:55:28 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	draw_slice_store_hit(t_data *d, t_cast *c, int col)
{
	int				start_end[2];
	int				h;
	int				start;
	unsigned int	color;

	if (c->perp < 1e-6)
		c->perp = 1e-6;
	h = (int)(d->win_h / c->perp);
	start_end[0] = -h / 2 + d->win_h / 2 + d->pitch;
	start_end[1] = h / 2 + d->win_h / 2 + d->pitch;
	if (start_end[0] < 0)
		start_end[0] = 0;
	if (start_end[1] >= d->win_h)
		start_end[1] = d->win_h - 1;
	if (c->side)
		color = 0x888888;
	else
		color = 0xBBBBBB;
	draw_line(d, col, start_end, color);
	d->hit_x[col] = d->pos_x + c->rx * c->perp;
	d->hit_y[col] = d->pos_y + c->ry * c->perp;
}

void	cast_and_draw_column(t_data *d, int col)
{
	t_cast	c;

	cast_init_ray(d, &c, col);
	cast_init_dda(d, &c);
	cast_step_to_hit(d, &c);
	draw_slice_store_hit(d, &c, col);
}
