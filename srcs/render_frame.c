/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:13:13 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../includes/cub3d.h"
#include "../includes/overlay.h"

int	render_frame(void *param)
{
	static double	last = 0.0;
	t_data			*d;
	double			now;
	double			dt;
	int				col;

	d = (t_data *)param;
	now = (double)clock() / CLOCKS_PER_SEC;
	dt = now - last;
	if (last == 0.0)
		dt = 0.016;
	last = now;
	move_player(d, dt);
	mm_compute_rect(d);
	draw_sky_floor(d);
	col = -1;
	while (++col < d->win_w)
		cast_and_draw_column(d, col);
	draw_minimap_overlay(d);
	mlx_put_image_to_window(d->mlx,
		d->win, d->img, 0, 0);
	return (0);
}
