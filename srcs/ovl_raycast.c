/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:10:49 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/10 13:04:14 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/cub3d.h"
#include "../includes/overlay.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*
** Build the ray for screen column `col`.
**
** cam_x ∈ [-1, 1] maps the column to camera space:
**   left edge  -> -1
**   center     ->  0
**   right edge -> +1
**
** Ray dir = player_dir + camera_plane * cam_x
** map_(x|y) is the current integer cell the player is in (floor of position).
*/
void	cast_init_ray(t_data *d, t_cast *c, int col)
{
	c->cam_x = 2.0 * col / (double)d->win_w - 1.0;
	c->rx = d->dir_x + d->plane_x * c->cam_x; /* ray x-direction */
	c->ry = d->dir_y + d->plane_y * c->cam_x; /* ray y-direction */
	c->map_x = (int)d->pos_x;
	c->map_y = (int)d->pos_y;
}

/*
** Prepare for DDA (Digital Differential Analyzer) grid stepping.
**
** dx, dy: distance the ray has to travel along the ray to cross one grid line
**         in X or Y (a.k.a. "deltaDistX/Y" in many tutorials).
** step_x, step_y: which direction we move in the map grid when we take a step
** sx, sy: distance from the player position to the first grid boundary in X or Y
**
** After this, we will repeatedly advance the closest side (x or y) until we hit.
*/
void	cast_init_dda(t_data *d, t_cast *c)
{
	/* Avoid division by zero when the ray is almost axis-aligned */
	c->dx = (fabs(c->rx) < 1e-9) ? 1e30 : fabs(1.0 / c->rx);
	c->dy = (fabs(c->ry) < 1e-9) ? 1e30 : fabs(1.0 / c->ry);

	/* Step direction for the grid in each axis */
	c->step_x = (c->rx < 0) ? -1 : 1;
	c->step_y = (c->ry < 0) ? -1 : 1;

	/*
	** Distance from the player to the first vertical/horizontal grid line
	** along the ray. This sets up the starting side distances.
	*/
	if (c->rx < 0)
		c->sx = (d->pos_x - c->map_x) * c->dx;
	else
		c->sx = (c->map_x + 1.0 - d->pos_x) * c->dx;

	if (c->ry < 0)
		c->sy = (d->pos_y - c->map_y) * c->dy;
	else
		c->sy = (c->map_y + 1.0 - d->pos_y) * c->dy;

	c->side = 0; /* 0 = we hit a vertical wall (x-side); 1 = horizontal (y-side) */
}

/*
** Take one DDA step:
**   - Choose the smaller of sx (next X boundary) and sy (next Y boundary).
**   - Advance to that boundary, move one grid cell in that axis.
**   - Check map cell for collision.
**
** We also clamp to map bounds to be safe.
*/
void	cast_step_to_hit_check(t_data *d, t_cast *c, int *hit)
{
	if (c->sx < c->sy)
	{
		c->sx += c->dx;        /* move to next vertical grid line */
		c->map_x += c->step_x; /* move one cell in X */
		c->side = 0;           /* vertical wall */
	}
	else
	{
		c->sy += c->dy;        /* move to next horizontal grid line */
		c->map_y += c->step_y; /* move one cell in Y */
		c->side = 1;           /* horizontal wall */
	}

	/* Clamp to valid map range */
	if (c->map_x < 0)            c->map_x = 0;
	if (c->map_y < 0)            c->map_y = 0;
	if (c->map_x >= d->map_w)    c->map_x = d->map_w - 1;
	if (c->map_y >= d->map_h)    c->map_y = d->map_h - 1;

	/* If this map cell is solid (>0), we hit a wall */
	if (d->c3d->point[c->map_y][c->map_x].access > 0)
		*hit = 1;
}

/*
** Keep stepping until we hit. Then compute perpendicular distance:
**   - If we just crossed a vertical grid line (side==0), the true perpendicular
**     distance is the sideDistanceX minus one delta (we already added one step).
**   - Same logic for horizontal (side==1) with Y distances.
**
** This fixes the fisheye effect (we use a perpendicular distance to the camera
** plane, not the raw Euclidean distance to the wall hit).
*/
void	cast_step_to_hit(t_data *d, t_cast *c)
{
	int	hit;

	hit = 0;
	while (!hit)
		cast_step_to_hit_check(d, c, &hit);

	if (c->side == 0)
		c->perp = c->sx - c->dx; /* last completed X step */
	else
		c->perp = c->sy - c->dy; /* last completed Y step */
}
