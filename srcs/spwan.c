/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spwan.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/12 19:10:53 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dir(t_data *d, double dx, double dy)
{
	d->dir_x = dx;
	d->dir_y = dy;
}

void	set_plane(t_data *d, double px, double py)
{
	d->plane_x = px;
	d->plane_y = py;
}

void	apply_spawn_orientation(t_data *d)
{
	double	pl;

	pl = 0.66;
	if (d->c3d->spawn == 'N')
	{
		set_dir(d, 0.0, -1.0);
		set_plane(d, pl, 0.0);
	}
	else if (d->c3d->spawn == 'S')
	{
		set_dir(d, 0.0, 1.0);
		set_plane(d, -pl, 0.0);
	}
	else if (d->c3d->spawn == 'E')
	{
		set_dir(d, 1.0, 0.0);
		set_plane(d, 0.0, pl);
	}
	else if (d->c3d->spawn == 'W')
	{
		set_dir(d, -1.0, 0.0);
		set_plane(d, 0.0, -pl);
	}
}
