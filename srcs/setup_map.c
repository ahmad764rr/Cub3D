/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:06:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 20:06:34 by nqasem           ###   ########.fr       */
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
