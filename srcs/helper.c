/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:05:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 20:04:52 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_line_points_lock(char *line, int unlocked_on[2], int *x)
{
	int	length;

	*x = 0;
	unlocked_on[0] = 0;
	unlocked_on[1] = -1;
	length = ft_strlen(line);
	while (length--)
	{
		if (line[length] == '1' || line[length] == '0')
		{
			unlocked_on[1] = length;
			break ;
		}
	}
}

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

int	handle_locked_map(t_cub3d **cub3d, char *map_line, int *y)
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
			&& (map_line[(*cub3d)->player.map_x] == 'N'
				|| map_line[(*cub3d)->player.map_x] == 'E'
				|| map_line[(*cub3d)->player.map_x] == 'S'
				|| map_line[(*cub3d)->player.map_x] == 'W'))
			(*cub3d)->player.map_y = (*y);
		(*y)++;
	}
	return (0);
}

int	handle_unlocked_map(char *map_line, int *lock)
{
	if (ft_strncmp(map_line, "1", 1) == 0 || ft_strncmp(map_line, "0", 1) == 0
		|| ft_strncmp(map_line, " ", 1) == 0)
	{
		(*lock) = 1;
		return (1);
	}
	return (3);
}

int	check_map_condtion(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	if (*lock)
		return (handle_locked_map(cub3d, map_line, y));
	else
		return (handle_unlocked_map(map_line, lock));
}
