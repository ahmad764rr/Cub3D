/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:20:00 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/04 14:06:41 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	cast_init_ray(t_data *d, t_cast *c, int col)
{
	c->cam_x = 2.0 * col / (double)d->win_w - 1.0;
	c->rx = d->dir_x + d->plane_x * c->cam_x;
	c->ry = d->dir_y + d->plane_y * c->cam_x;
	c->map_x = (int)d->pos_x;
	c->map_y = (int)d->pos_y;
}

void	cast_init_dda(t_data *d, t_cast *c)
{
	if (fabs(c->rx) < 1e-9)
		c->dx = 1e30;
	else
		c->dx = fabs(1.0 / c->rx);
	if (fabs(c->ry) < 1e-9)
		c->dy = 1e30;
	else
		c->dy = fabs(1.0 / c->ry);
	if (c->rx < 0)
		c->step_x = -1;
	else
		c->step_x = 1;
	if (c->ry < 0)
		c->step_y = -1;
	else
		c->step_y = 1;
	if (c->rx < 0)
		c->sx = (d->pos_x - c->map_x) * c->dx;
	else
		c->sx = (c->map_x + 1.0 - d->pos_x) * c->dx;
	if (c->ry < 0)
		c->sy = (d->pos_y - c->map_y) * c->dy;
	else
		c->sy = (c->map_y + 1.0 - d->pos_y) * c->dy;
	c->side = 0;
}

void	cast_step_to_hit_check(t_data *d, t_cast *c, int *hit)
{
		if (c->sx < c->sy)
		{
			c->sx += c->dx;
			c->map_x += c->step_x;
			c->side = 0;
		}
		else
		{
			c->sy += c->dy;
			c->map_y += c->step_y;
			c->side = 1;
		}
		if (c->map_x < 0)
			c->map_x = 0;
		if (c->map_y < 0)
			c->map_y = 0;
		if (c->map_x >= d->map_w)
			c->map_x = d->map_w - 1;
		if (c->map_y >= d->map_h)
			c->map_y = d->map_h - 1;
		if (d->c3d->point[c->map_y][c->map_x].access > 0)
			*hit = 1;
}

void	cast_step_to_hit(t_data *d, t_cast *c)
{
	int	hit;

	hit = 0;
	while (!hit)
		cast_step_to_hit_check(d, c, &hit);
	if (c->side == 0)
		c->perp = c->sx - c->dx;
	else
		c->perp = c->sy - c->dy;
}

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
