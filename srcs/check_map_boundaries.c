/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_boundaries.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:03:43 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/15 21:05:13 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_boundary_invalid(int access)
{
	if (access != 1 && access != 3 && access != 4)
		return (1);
	return (0);
}

static int	is_adjacent_invalid(t_cub3d **cub3d, int x, int y)
{
	if ((*cub3d)->point[y][x].access != 0)
		return (0);
	if ((*cub3d)->point[y][x + 1].access == 3
		|| (*cub3d)->point[y][x - 1].access == 3
		|| (*cub3d)->point[y + 1][x].access == 3
		|| (*cub3d)->point[y - 1][x].access == 3
		|| (*cub3d)->point[y][x + 1].access == 4
		|| (*cub3d)->point[y][x - 1].access == 4
		|| (*cub3d)->point[y + 1][x].access == 4
		|| (*cub3d)->point[y - 1][x].access == 4)
		return (1);
	return (0);
}

int	check_map_boundaries(t_cub3d **cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < (*cub3d)->map.map_height)
	{
		x = 0;
		while (x < (*cub3d)->map.map_width)
		{
			if ((y == 0 || y == (*cub3d)->map.map_height - 1
					|| x == 0 || x == (*cub3d)->map.map_width - 1)
				&& is_boundary_invalid((*cub3d)->point[y][x].access))
				return (-1);
			if (is_adjacent_invalid(cub3d, x, y))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
