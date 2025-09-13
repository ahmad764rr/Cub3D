/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/10 14:43:54 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
	draw_sky_floor(d);
	col = -1;
	while (++col < d->win_w)
		cast_and_draw_column(d, col);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}
