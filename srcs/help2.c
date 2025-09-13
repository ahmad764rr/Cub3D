/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:06:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 20:06:34 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	handle_spawn_char(t_cub3d **cub3d, char c, int i)
{
	if ((*cub3d)->player.map_x == -1)
	{
		(*cub3d)->spawn = c;
		(*cub3d)->player.map_x = i;
		return (0);
	}
	if ((*cub3d)->player.map_y != -1)
		return (-1);
	return (0);
}

int	check_map_values_condtion(t_cub3d **cub3d, char *line, int *check_empty)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (line[i])
	{
		if (is_spawn_char(line[i]))
			error++;
		if (!ft_isspace(line[i]))
			*check_empty = 0;
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i])
			&& !is_spawn_char(line[i]))
			return (-1);
		else if (is_spawn_char(line[i]))
			if (handle_spawn_char(cub3d, line[i], i) == -1)
				return (-1);
		i++;
	}
	if (error > 1)
		return (-1);
	return (0);
}
