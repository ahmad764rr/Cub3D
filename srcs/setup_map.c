/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:06:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 17:25:15 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_values(char *line, t_cub3d **cub3d, int which)
{
	int	i;
	int	value;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isdigit(line[i]) || line[i] == '+' || line[i] == '-')
	{
		value = ft_atoi(line + i);
		if (value < 0 || value > 255)
			return (-1);
		set_color_data(value, cub3d, which);
		while (ft_isdigit(line[i]) || line[i] == '+' || line[i] == '-')
			i++;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == ',')
			i++;
		else if (line[i] != '\0')
			return (-1);
		while (ft_isspace(line[i]))
			i++;
	}
	return (0);
}

int	setup_check_map(t_cub3d **cub3d, char **map_line)
{
	if (open_file(cub3d) == -1)
	{
		handle_error(ERO_OPEN_FILE);
		return (-1);
	}
	(*map_line) = get_next_line((*cub3d)->fd);
	if (!(*map_line))
		return (-1);
	(*cub3d)->point = (t_point **)malloc(sizeof(t_point *)
			* ((*cub3d)->map.map_height));
	if (!(*cub3d)->point)
	{
		handle_get_next_line((*cub3d)->fd, *map_line);
		(*cub3d)->map.map_height = -1;
		handle_error(ERO_MALLOC);
		return (-1);
	}
	return (0);
}

void	set_map_values(t_cub3d **cub3d, char *line, int y)
{
	int	x;
	int	size;

	x = 0;
	size = ft_strlen(line);
	while (line[x])
	{
		if (line[x] == ' ')
			(*cub3d)->point[y][x].access = 0;
		else if ((line[x] == 'N' || line[x] == 'E' 
			|| line[x] == 'S' || line[x] == 'W'))
			(*cub3d)->point[y][x].access = 0;
		else
		(*cub3d)->point[y][x].access = line[x] - '0';
		(*cub3d)->point[y][x].x = x;
		(*cub3d)->point[y][x].y = y;
		(*cub3d)->point[y][x].width = size;
		x++;
	}
	while (x < (*cub3d)->map.map_width)
	{
		(*cub3d)->point[y][x].access = 3;
		(*cub3d)->point[y][x].x = x;
		(*cub3d)->point[y][x].y = y;
		x++;
	}
}

int	check_map_values_condtion(t_cub3d **cub3d, char *line, int *check_empty)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			(*check_empty) = 0;
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i])
			&& line[i] != 'N' && line[i] != 'W' && line[i] != 'E' && line[i] != 'S')
			return (-1);
		else if ((line[i] == 'N' || line[i] == 'E' 
			|| line[i] == 'S' || line[i] == 'W') && (*cub3d)->player.map_x == -1)
			{
				(*cub3d)->spawn = line[i];
				(*cub3d)->player.map_x = i;
			}
		else if ((line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'W') && (*cub3d)->player.map_y != -1)
			return (-1);
		i++;
	}
	return (0);
}

int	check_map_values(t_cub3d **cub3d, char *line, int y)
{
	int		check_empty;
	char	*temp;

	check_empty = 1;
	if (check_map_values_condtion(cub3d, line, &check_empty) == -1)
		return (-1);
	if (!check_empty && (*cub3d)->is_empty == 1)
		return (-1);
	if (check_empty)
		(*cub3d)->is_empty = 1;
	if (check_empty == 0)
	{
		(*cub3d)->point[y] = (t_point *)malloc((sizeof(t_point))
				* ((*cub3d)->map.map_width));
		if (!(*cub3d)->point[y])
		{
			handle_error(ERO_MALLOC);
			return (-1);
		}
		temp = ft_strtrim(line, "\t\n\r");
		set_map_values(cub3d, temp, y);
		free(temp);
	}
	return (0);
}
