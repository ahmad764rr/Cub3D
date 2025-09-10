/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:10:46 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/10 13:38:07 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void	draw_line(t_data *d, int x01, int y01[], unsigned int c)
{
	int   x0 = x01;
	int   y0 = y01[0];
	int   x1 = x01;
	int   y1 = y01[1];

	int dx = x1 - x0;
	int dy = y1 - y0;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	if (steps == 0)
	{
		put_pixel(d, x0, y0, c);
		return;
	}

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float x = x0;
	float y = y0;

	for (int i = 0; i <= steps; i++)
	{
		put_pixel(d, (int)roundf(x), (int)roundf(y), c);
		x += x_inc;
		y += y_inc;
	}
}
