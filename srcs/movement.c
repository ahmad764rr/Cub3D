/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/10 21:11:47 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"
#include <math.h>

void	move_fwd_back(t_data *d, double ms)
{
	double	nx;
	double	ny;

	// ms = 0.04;
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

void	move_player(t_data *d, double dt)
{
	double	ms;
	double	rs;

	ms = dt * 5.0;
	rs = dt * 3.0;
	move_fwd_back(d, ms);
	rotate_dir_plane(d, rs);
}
