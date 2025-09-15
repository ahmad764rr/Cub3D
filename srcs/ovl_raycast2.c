/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_raycast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:24 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/15 16:03:42 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

static int pick_tex_id(t_cast *c)
{
    if (c->side == 0)
    {
        if (c->rx > 0)
            return 3;   
        else
            return 2;
    }
    else
    {
        if (c->ry > 0)
            return 1;  
        else
            return 0;
    }
}

static void	setup_slice(t_data *d, t_cast *c, t_slice *s)
{
	double	wall_x;

	if (c->perp < 1e-6)
		c->perp = 1e-6;
	s->h = (int)(d->win_h / c->perp);
	s->draw_start = -s->h / 2 + d->win_h / 2;
	s->draw_end = s->h / 2 + d->win_h / 2;
	if (s->draw_start < 0)
		s->draw_start = 0;
	if (s->draw_end >= d->win_h)
		s->draw_end = d->win_h - 1;
	s->tex = &d->tex[pick_tex_id(c)];
	if (c->side == 0)
		wall_x = d->pos_y + c->perp * c->ry;
	else
		wall_x = d->pos_x + c->perp * c->rx;
	wall_x -= floor(wall_x);
	s->tex_x = (int)(wall_x * (double)s->tex->width);
	if (c->side == 0 && c->rx < 0)       
    	s->tex_x = s->tex->width - s->tex_x - 1;
	if (c->side == 1 && c->ry > 0)       
    	s->tex_x = s->tex->width - s->tex_x - 1;

	s->step = (double)s->tex->height / (double)s->h;
	s->tex_pos = (s->draw_start - (d->win_h / 2) + s->h / 2.0) * s->step;
}

static void	draw_slice(t_data *d, t_slice *s, int col)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = s->draw_start;
	while (y <= s->draw_end)
	{
		tex_y = (int)(s->tex_pos);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= s->tex->height)
			tex_y = s->tex->height - 1;
		color = tex_get_pixel(s->tex, s->tex_x, tex_y);
		put_pixel(d, col, y, color);
		s->tex_pos += s->step;
		y++;
	}
}

void	draw_slice_store_hit(t_data *d, t_cast *c, int col)
{
	t_slice	s;

	setup_slice(d, c, &s);
	draw_slice(d, &s, col);
}

void	cast_and_draw_column(t_data *d, int col)
{
	t_cast	c;

	cast_init_ray(d, &c, col);
	cast_init_dda(d, &c);
	cast_step_to_hit(d, &c);
	draw_slice_store_hit(d, &c, col);
}
