/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:06:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 20:06:34 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_line_points(t_cub3d **cub3d, char *line, int y, int size)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == ' ')
			(*cub3d)->point[y][x].access = 0;
		else if (line[x] == 'N' || line[x] == 'E'
			|| line[x] == 'S' || line[x] == 'W')
			(*cub3d)->point[y][x].access = 0;
		else
			(*cub3d)->point[y][x].access = line[x] - '0';
		(*cub3d)->point[y][x].x = x;
		(*cub3d)->point[y][x].y = y;
		(*cub3d)->point[y][x].width = size;
		x++;
	}
}

void	fill_padding_points(t_cub3d **cub3d, int y, int start)
{
	while (start < (*cub3d)->map.map_width)
	{
		(*cub3d)->point[y][start].access = 3;
		(*cub3d)->point[y][start].x = start;
		(*cub3d)->point[y][start].y = y;
		start++;
	}
}

void	set_map_values(t_cub3d **cub3d, char *line, int y)
{
	int	size;

	size = ft_strlen(line);
	fill_line_points(cub3d, line, y, size);
	fill_padding_points(cub3d, y, size);
}

int	alloc_and_fill_points(t_cub3d **cub3d, char *line, int y)
{
	char	*temp;

	(*cub3d)->point[y] = (t_point *)malloc(sizeof(t_point)
			* (*cub3d)->map.map_width);
	if (!(*cub3d)->point[y])
	{
		handle_error(ERO_MALLOC);
		return (-1);
	}
	temp = ft_strtrim(line, "\t\n\r");
	set_map_values(cub3d, temp, y);
	free(temp);
	return (0);
}

int	check_map_values(t_cub3d **cub3d, char *line, int y)
{
	int	check_empty;

	check_empty = 1;
	if (check_map_values_condtion(cub3d, line, &check_empty) == -1)
		return (-1);
	if (!check_empty && (*cub3d)->is_empty == 1)
		return (-1);
	if (check_empty)
		(*cub3d)->is_empty = 1;
	if (check_empty == 0)
		if (alloc_and_fill_points(cub3d, line, y) == -1)
			return (-1);
	return (0);
}
