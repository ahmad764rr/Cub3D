/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:13:13 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/cub3d.h"
#include "../includes/overlay.h"

static int	alloc_c3d(t_cub3d **c3d)
{
	*c3d = malloc(sizeof(**c3d));
	if (!*c3d)
		return (1);
	return (0);
}

static int	setup_game(t_data *d, t_cub3d *c3d, char *path)
{
	if (init_cub3d(c3d, path), parsing_manager(&c3d) == -1)
	{
		free(c3d);
		exit(1);
	}
	*d = (t_data){0};
	d->c3d = c3d;
	d->map_w = c3d->map.map_width;
	d->map_h = c3d->map.map_height;
	d->win_w = WIN_W;
	d->win_h = WIN_H;
	init_player_camera(d);
	if (init_gfx(d))
		return (1);
	if (alloc_ray_buffers(d))
		return (1);
	return (0);
}

static void	set_hooks(t_data *d)
{
	mlx_hook(d->win, 2, 1L << 0, key_press, d);
	mlx_hook(d->win, 3, 1L << 1, key_release, d);
	mlx_hook(d->win, 17, 0, close_game, d);
	mlx_loop_hook(d->mlx, render_frame, d);
}

static int	cleanup_and_exit(t_data *d, t_cub3d *c3d, int code)
{
	free(d->hit_x);
	free(d->hit_y);
	free_texture(c3d);
	free_map_points(c3d);
	free(c3d);
	return (code);
}

int	main(int argc, char **argv)
{
	t_cub3d	*c3d;
	t_data	d;

	if (argc != 2)
	{
		ft_putendl_fd(ERO_USA, 2);
		return (1);
	}
	if (alloc_c3d(&c3d))
		return (1);
	if (setup_game(&d, c3d, argv[1]))
		return (cleanup_and_exit(&d, c3d, 1));
	set_hooks(&d);
	mlx_loop(d.mlx);
	return (cleanup_and_exit(&d, c3d, 0));
}
