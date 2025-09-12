/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:05:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 18:55:13 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_points(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!cub3d->point || !cub3d)
		return ;
	while (i < cub3d->map.map_height)
	{
		free(cub3d->point[i]);
		i++;
	}
	free(cub3d->point);
}

int	check_map_condtion(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	if ((*lock))
	{
		if (check_map_values(cub3d, map_line, (*y)) == -1)
		{
			(*cub3d)->map.map_height = (*y);
			handle_get_next_line((*cub3d)->fd, map_line);
			return (-1);
		}
		if ((*cub3d)->is_empty == 0)
		{
			if ((*cub3d)->player.map_x != -1 && (*cub3d)->player.map_y == -1
				&& (map_line[(*cub3d)->player.map_x] == 'N' || map_line[(*cub3d)->player.map_x] == 'E'
				|| map_line[(*cub3d)->player.map_x] == 'S' || map_line[(*cub3d)->player.map_x] == 'W'))
				(*cub3d)->player.map_y = (*y);
			(*y)++;
		}
	}
	else if (ft_strncmp(map_line, "1", 1) == 0 || ft_strncmp(map_line, "0",
			1) == 0 || ft_strncmp(map_line, " ", 1) == 0)
	{
		(*lock) = 1;
		return (1);
	}
	else
		return (3);
	return (0);
}

int	check_map_searching_2(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	int		ret;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(map_line, " \t\n\r");
	if ((*lock) == 0 && trimmed_line[0] != '1' && trimmed_line[0] != '0'
		&& trimmed_line[0] != 'N' && trimmed_line[0] != 'E' && trimmed_line[0] != 'S' && trimmed_line[0] != 'W')
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

int	check_map_searching(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	char *trimmed_line;
	int	ret;
	int	i;

	i = 0;
	(*cub3d)->is_empty = 0;
	while (map_line)
	{
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
			continue ;
		i++;
		free(map_line);
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
