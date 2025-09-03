/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/03 13:26:59 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

void	init_player_camera(t_data *d)
{
	d->pitch = 0;
	d->pos_x = d->c3d->player.map_x + 0.5;
	d->pos_y = d->c3d->player.map_y + 0.5;
	d->dir_x = -1.0;
	d->dir_y = 0.0;
	d->plane_x = 0.0;
	d->plane_y = 0.66;
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
		handle_error("ray buffer alloc failed");
		return (1);
	}
	return (0);
}
