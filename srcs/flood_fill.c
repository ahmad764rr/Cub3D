/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:08:17 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/13 15:34:04 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_out_of_bounds(int x, int y, t_map *map)
{
	return (x < 0 || x >= map->map_width || y < 0 || y >= map->map_height);
}

int	flood_fill(t_map *map, int x, int y, t_cub3d *cub3d)
{
	int	result;

	if (is_out_of_bounds(x, y, map))
		return (0);
	if (cub3d->point[y][x].access == 1 || cub3d->point[y][x].access == 3
		|| cub3d->point[y][x].access == 4 || map->visited[y][x])
		return (1);
	map->visited[y][x] = 1;
	result = 1;
	result &= flood_fill(map, x + 1, y, cub3d);
	result &= flood_fill(map, x - 1, y, cub3d);
	result &= flood_fill(map, x, y + 1, cub3d);
	result &= flood_fill(map, x, y - 1, cub3d);
	return (result);
}

int	**alloc_2d_array(int height, int width)
{
	int	i;
	int	**arr;

	arr = malloc(height * sizeof(int *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < height)
	{
		arr[i] = ft_calloc(width, sizeof(int));
		if (!arr[i])
			return (NULL);
		i++;
	}
	return (arr);
}

void	free_2d_array(int **arr, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	setup_flood_fill(t_cub3d *cub3d)
{
	cub3d->map.visited = alloc_2d_array(cub3d->map.map_height,
			cub3d->map.map_width);
	if (!cub3d->map.visited)
	{
		handle_error(ERO_MALLOC);
		return (-1);
	}
	if (!flood_fill(&cub3d->map, cub3d->player.map_x, cub3d->player.map_y,
			cub3d))
	{
		free_2d_array(cub3d->map.visited, cub3d->map.map_height);
		write(1, ERO_CLOSED_MAP, ft_strlen(ERO_CLOSED_MAP));
		return (-1);
	}
	free_2d_array(cub3d->map.visited, cub3d->map.map_height);
	return (0);
}
