/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:08:29 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/15 16:14:00 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_status(t_cub3d **cub3d)
{
	int	is_complete;

	is_complete = 0;
	if (handle_read_file(cub3d, &is_complete) == -1)
	{
		free_texture(*cub3d);
		close((*cub3d)->fd);
		return (-1);
	}
	if (is_complete != 6 || (*cub3d)->map.map_height == -1)
	{
		free_texture(*cub3d);
		check_data_error(cub3d, ERO_MAP, 6);
		close((*cub3d)->fd);
		return (-1);
	}
	return (0);
}

void	set_texture_data(char *line, int skip, t_cub3d **cub3d)
{
	char	*trimmed_line;
	int		i;

	i = skip;
	while (ft_isspace(line[i]))
		i++;
	trimmed_line = ft_strchr(line + skip, line[i]);
	if (!trimmed_line)
	{
		handle_error(ERO_MAP);
		return ;
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		(*cub3d)->map.texture_north
			= valid_set_texture_data((*cub3d)->map.texture_north, trimmed_line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		(*cub3d)->map.texture_south
			= valid_set_texture_data((*cub3d)->map.texture_south, trimmed_line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		(*cub3d)->map.texture_west
			= valid_set_texture_data((*cub3d)->map.texture_west, trimmed_line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		(*cub3d)->map.texture_east
			= valid_set_texture_data((*cub3d)->map.texture_east, trimmed_line);
}

void	init_cub3d(t_cub3d *cub3d, char *arg)
{
	cub3d->fd = -1;
	cub3d->flag = 0;
	cub3d->is_empty = -1;
	cub3d->map.map_height = -1;
	cub3d->map.map_width = -1;
	cub3d->map.file_path = NULL;
	cub3d->map.data = NULL;
	cub3d->map.texture_north = NULL;
	cub3d->map.texture_south = NULL;
	cub3d->map.texture_west = NULL;
	cub3d->map.texture_east = NULL;
	cub3d->map.texture_sprite = NULL;
	cub3d->map.color_floor.r = -1;
	cub3d->map.color_floor.g = -1;
	cub3d->map.color_floor.b = -1;
	cub3d->map.color_ceiling.r = -1;
	cub3d->map.color_ceiling.g = -1;
	cub3d->map.color_ceiling.b = -1;
	cub3d->file_path = arg;
	cub3d->player.map_x = -1;
	cub3d->player.map_y = -1;
}

void	set_color_data(int value, t_cub3d **cub3d, int which)
{
	static int	floor_i = 0;
	static int	ceil_i = 0;

	if (which == 'F')
	{
		if (floor_i == 0)
			(*cub3d)->map.color_floor.r = value;
		else if (floor_i == 1)
			(*cub3d)->map.color_floor.g = value;
		else if (floor_i == 2)
			(*cub3d)->map.color_floor.b = value;
		floor_i++;
	}
	else if (which == 'C')
	{
		if (ceil_i == 0)
			(*cub3d)->map.color_ceiling.r = value;
		else if (ceil_i == 1)
			(*cub3d)->map.color_ceiling.g = value;
		else if (ceil_i == 2)
			(*cub3d)->map.color_ceiling.b = value;
		ceil_i++;
	}
}
