/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/12 17:27:30 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"
void	apply_spawn_orientation(t_data *d);
void	init_player_camera(t_data *d)
{
	d->pitch = 0;
	d->pos_x = d->c3d->player.map_x + 0.5;
	d->pos_y = d->c3d->player.map_y + 0.5;
	d->dir_x = 0.0;
	d->dir_y = 0.0;
	d->plane_x = 0;
	d->plane_y = 0.0;
	apply_spawn_orientation(d);
}
void	apply_spawn_orientation(t_data *d)
{
	double	pl;

	pl = 0.66;
	if (d->c3d->spawn == 'N')
	{
		d->dir_x = 0.0;
		d->dir_y = -1.0;
		d->plane_x = pl;
		d->plane_y = 0.0;
	}
	else if (d->c3d->spawn == 'S')
	{
		d->dir_x = 0.0;
		d->dir_y = 1.0;
		d->plane_x = -pl;
		d->plane_y = 0.0;
	}
	else if (d->c3d->spawn == 'E')
	{
		d->dir_x = 1.0;
		d->dir_y = 0.0;
		d->plane_x = 0.0;
		d->plane_y = pl;
	}
	else if (d->c3d->spawn == 'W')
	{
		d->dir_x = -1.0;
		d->dir_y = 0.0;
		d->plane_x = 0.0;
		d->plane_y = -pl;
	}
}
int	init_gfx(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		return (handle_error(ERO_MLX_INIT), 1);
	d->win = mlx_new_window(d->mlx, d->win_w, d->win_h, "cub3d");
	if (!d->win)
		return (handle_error(ERO_MLX_WIN), 1);
	d->img = mlx_new_image(d->mlx, d->win_w, d->win_h);
	if (!d->img)
		return (handle_error(ERO_MLX_IMG), 1);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	if (!d->addr)
		return (handle_error(ERO_MLX_ADDR), 1);
	return (0);
}

int	alloc_ray_buffers(t_data *d)
{
	d->hit_x = (double *)malloc(sizeof(double) * d->win_w);
	d->hit_y = (double *)malloc(sizeof(double) * d->win_w);
	if (!d->hit_x || !d->hit_y)
	{
		handle_error("Error\nray buffer alloc failed");
		return (1);
	}
	return (0);
}
