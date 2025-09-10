/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:10:46 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/10 14:39:27 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"
#include <math.h>

static void	line_init(t_line *l, int x, int y0, int y1)
{
	l->x0 = x;
	l->y0 = y0;
	l->x1 = x;
	l->y1 = y1;
	l->dx = l->x1 - l->x0;
	l->dy = l->y1 - l->y0;
	l->steps = abs(l->dx);
	if (abs(l->dy) > l->steps)
		l->steps = abs(l->dy);
	l->x_inc = l->dx / (float)l->steps;
	l->y_inc = l->dy / (float)l->steps;
	l->x = l->x0;
	l->y = l->y0;
}

static void	line_draw_pixels(t_data *d, t_line *l, unsigned int c)
{
	int	i;

	if (l->steps == 0)
	{
		put_pixel(d, l->x0, l->y0, c);
		return ;
	}
	i = 0;
	while (i <= l->steps)
	{
		put_pixel(d, (int)roundf(l->x), (int)roundf(l->y), c);
		l->x += l->x_inc;
		l->y += l->y_inc;
		i++;
	}
}

void	draw_line(t_data *d, int x01, int y01[], unsigned int c)
{
	t_line	l;

	line_init(&l, x01, y01[0], y01[1]);
	line_draw_pixels(d, &l, c);
}
