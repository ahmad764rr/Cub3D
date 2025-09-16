/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:05:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 20:04:52 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_searching_2(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	int		ret;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(map_line, " \t\n\r");
	if ((*lock) == 0 && trimmed_line[0] != '1' && trimmed_line[0] != '0'
		&& trimmed_line[0] != 'N' && trimmed_line[0] != 'E'
		&& trimmed_line[0] != 'S' && trimmed_line[0] != 'W')
		ret = check_map_condtion(cub3d, trimmed_line, lock, y);
	else
		ret = check_map_condtion(cub3d, map_line, lock, y);
	free(trimmed_line);
	if (ret == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	if (ret == 3 && (*lock) == 1)
	{
		(*cub3d)->map.map_height = (*y);
		handle_get_next_line((*cub3d)->fd, map_line);
		return (-1);
	}
	return (0);
}

static int	process_line(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_strtrim(map_line, " ");
	if (trimmed_line[0] != '1' && trimmed_line[0] != '0')
	{
		free(map_line);
		map_line = trimmed_line;
	}
	else
		free(trimmed_line);
	ret = check_map_searching_2(cub3d, map_line, lock, y);
	if (ret == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	free(map_line);
	return (0);
}

int	check_map_searching(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	int	ret;

	(*cub3d)->is_empty = 0;
	while (map_line)
	{
		ret = process_line(cub3d, map_line, lock, y);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			continue ;
		map_line = get_next_line((*cub3d)->fd);
	}
	return (0);
}

int	check_map(t_cub3d **cub3d)
{
	char	*map_line;
	int		lock;
	int		y;

	lock = 0;
	y = 0;
	close((*cub3d)->fd);
	(*cub3d)->fd = -1;
	if (setup_check_map(cub3d, &map_line) == -1)
		return (-1);
	if (check_map_searching(cub3d, map_line, &lock, &y) < 0)
		return (-1);
	if ((*cub3d)->player.map_x == -1 || (*cub3d)->player.map_y == -1)
	{
		(*cub3d)->map.map_height = y;
		handle_error(ERO_MAP);
		return (-1);
	}
	(*cub3d)->map.map_height = y;
	return (0);
}
