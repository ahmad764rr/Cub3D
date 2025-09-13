/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:10:49 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/11 17:19:48 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
	c->dx = sqrt(1.0 + (c->ry * c->ry) / (c->rx * c->rx));
	c->dy = sqrt(1.0 + (c->rx * c->rx) / (c->ry * c->ry));
	if (fabs(c->rx) < 0)
		c->dx = 1e30;
	if (fabs(c->ry) < 0)
		c->dy = 1e30;
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
	int		hit;
	double	ray_angle;
	double	dir_angle;
	double	angle_diff;
	double	euclid_dist;

	hit = 0;
	while (!hit)
		cast_step_to_hit_check(d, c, &hit);
	ray_angle = atan2(c->ry, c->rx);
	dir_angle = atan2(d->dir_y, d->dir_x);
	angle_diff = ray_angle - dir_angle;
	if (c->side == 0)
		euclid_dist = c->sx - c->dx;
	else
		euclid_dist = c->sy - c->dy;
	c->perp = euclid_dist * cos(angle_diff);
}
