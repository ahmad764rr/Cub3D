/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_raycast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:24 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/10 13:55:51 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

/*
** Draw one vertical wall slice for screen column `col`, then store the exact
** world hit coordinate of the ray for overlay effects (minimap, markers...).
**
** Key idea:
**   - We already have c->perp = perpendicular distance to the wall (no fisheye).
**   - Wall height in pixels ~ screen_height / distance.
**   - We center the slice around the middle of the screen (+ pitch for head bob).
*/
void	draw_slice_store_hit(t_data *d, t_cast *c, int col)
{
	int				y_range[2];     /* y_range[0] = startY, y_range[1] = endY */
	int				h;              /* slice (wall) height on screen in pixels */
	unsigned int	color;

	/* Avoid divide-by-zero: clamp extremely small distances */
	if (c->perp < 1e-6)
		c->perp = 1e-6;

	/* Simple perspective: taller when closer, shorter when farther */
	h = (int)(d->win_h / c->perp);

	/* Center the wall slice vertically (middle of screen is d->win_h / 2) */
	y_range[0] = -h / 2 + d->win_h / 2; /* top Y */
	y_range[1] =  h / 2 + d->win_h / 2; /* bottom Y */

	/* Clip to window bounds */
	if (y_range[0] < 0)
		y_range[0] = 0;
	if (y_range[1] >= d->win_h)
		y_range[1] = d->win_h - 1;

	/* Simple shading: darken if we hit an NS wall (side=1), brighter for EW */
	color = (c->side) ? 0x888888 : 0xBBBBBB;

	/* Draw a single vertical line at x = col from y = start to y = end */
	draw_line(d, col, y_range, color);

	// /* Save the exact world-space intersection point for overlays */
	// d->hit_x[col] = d->pos_x + c->rx * c->perp;
	// d->hit_y[col] = d->pos_y + c->ry * c->perp;
}

/*
** Full pipeline for one screen column:
**   1) Build the ray direction from camera plane.
**   2) Prepare DDA (grid stepping) parameters.
**   3) Step the ray through the grid until it hits a wall.
**   4) Project and draw the wall slice, store hit point.
*/
void	cast_and_draw_column(t_data *d, int col)
{
	t_cast	c;

	cast_init_ray(d, &c, col);
	cast_init_dda(d, &c);
	cast_step_to_hit(d, &c);
	draw_slice_store_hit(d, &c, col);
}
