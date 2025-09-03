/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/03 13:38:18 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/overlay.h"

void	move_fwd_back(t_data *d, double ms)
{
	double	nx;
	double	ny;

	if (d->act_fwd)
	{
		nx = d->pos_x + d->dir_x * ms;
		ny = d->pos_y + d->dir_y * ms;
		if (d->c3d->point[(int)d->pos_y][(int)nx].access == 0)
			d->pos_x = nx;
		if (d->c3d->point[(int)ny][(int)d->pos_x].access == 0)
			d->pos_y = ny;
	}
	if (d->act_back)
	{
		nx = d->pos_x - d->dir_x * ms;
		ny = d->pos_y - d->dir_y * ms;
		if (d->c3d->point[(int)d->pos_y][(int)nx].access == 0)
			d->pos_x = nx;
		if (d->c3d->point[(int)ny][(int)d->pos_x].access == 0)
			d->pos_y = ny;
	}
}

void	move_strafe(t_data *d, double ms)
{
	double	side;
	double	sx;
	double	sy;

	if (!(d->act_left || d->act_right))
		return ;
	side = 0.0;
	if (d->act_left)
		side = 1.0;
	else
		side = -1.0;
	sx = side * d->dir_y * ms;
	sy = side * -d->dir_x * ms;
	if (d->c3d->point[(int)d->pos_y][(int)(d->pos_x + sx)].access == 0)
		d->pos_x += sx;
	if (d->c3d->point[(int)(d->pos_y + sy)][(int)d->pos_x].access == 0)
		d->pos_y += sy;
}

void	rotate_dir_plane(t_data *d, double rs)
{
	double	ang;
	double	odx;
	double	opx;

	if (!(d->act_turn_l || d->act_turn_r))
		return ;
	ang = rs;
	if (d->act_turn_r)
		ang = -rs;
	odx = d->dir_x;
	opx = d->plane_x;
	d->dir_x = d->dir_x * cos(ang) - d->dir_y * sin(ang);
	d->dir_y = odx * sin(ang) + d->dir_y * cos(ang);
	d->plane_x = d->plane_x * cos(ang) - d->plane_y * sin(ang);
	d->plane_y = opx * sin(ang) + d->plane_y * cos(ang);
}

void	update_pitch(t_data *d, double dt)
{
	int	speed;
	int	maxp;

	speed = (int)(dt * 600.0);
	if (d->look_up)
		d->pitch -= speed;
	if (d->look_down)
		d->pitch += speed;
	maxp = d->win_h / 2 - 10;
	if (d->pitch > maxp)
		d->pitch = maxp;
	if (d->pitch < -maxp)
		d->pitch = -maxp;
}

void	move_player(t_data *d, double dt)
{
	double	ms;
	double	rs;

	ms = dt * 5.0;
	rs = dt * 3.0;
	move_fwd_back(d, ms);
	move_strafe(d, ms);
	rotate_dir_plane(d, rs);
	update_pitch(d, dt);
}
