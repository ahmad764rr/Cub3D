/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:49:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/15 19:15:06 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_map_dimensions(t_cub3d **cub3d, char *line)
{
	int		i;
	int		width;
	char	*temp;

	i = 0;
	width = 0;
	temp = ft_strtrim(line, " \t\n\r");
	if (!temp)
		return (-1);
	if (temp[0] == '1' || temp[0] == '0')
	{
		free(temp);
		temp = ft_strtrim(line, "\n");
		width = ft_strlen(temp);
		if ((*cub3d)->map.map_width < width)
			(*cub3d)->map.map_width = width;
	}
	free(temp);
	return (0);
}

int	handle_read_file(t_cub3d **cub3d, int *is_complete)
{
	char	*line;

	line = get_next_line((*cub3d)->fd);
	if (!line)
	{
		check_data_error(cub3d, ERO_READ, 3);
		return (-1);
	}
	while (line)
	{
		if (setup_check_data(line, cub3d, is_complete) == -1)
		{
			handle_get_next_line((*cub3d)->fd, line);
			return (-1);
		}
		if (get_map_dimensions(cub3d, line) == -1)
		{
			handle_get_next_line((*cub3d)->fd, line);
			return (-1);
		}
		free(line);
		line = get_next_line((*cub3d)->fd);
	}
	return (0);
}

/* void	print(t_cub3d *cub3d)
{
	int	i;
	int	j;

	for (i = 0; i < cub3d->map.map_height; i++)
	{
		for (j = 0; j < cub3d->map.map_width; j++)
		{
			printf("%d ", cub3d->point[i][j].access);
		}
		printf("\n");
	}
	for (i = 0; i < cub3d->map.map_height; i++)
	{
		for (j = 0; j < cub3d->map.map_width; j++)
		{
			printf("(%d, %d)", cub3d->point[i][j].x, cub3d->point[i][j].y);
		}
		printf("\n");
	}
	printf("texture_north: %s\n", cub3d->map.texture_north);
	printf("texture_south: %s\n", cub3d->map.texture_south);
	printf("texture_west: %s\n", cub3d->map.texture_west);
	printf("texture_east: %s\n", cub3d->map.texture_east);
	printf("length of map: %d\n", cub3d->map.map_width);
	printf("height of map: %d\n", cub3d->map.map_height);
	printf("Player position: (%d, %d)\n", cub3d->player.map_x
	 , cub3d->player.map_y);
	printf("floor (%d, %d, %d)\n", cub3d->map.color_floor.r
	, cub3d->map.color_floor.g, cub3d->map.color_floor.b);
	printf("Cell (%d, %d, %d)\n", cub3d->map.color_ceiling.r,
	 cub3d->map.color_ceiling.g, cub3d->map.color_ceiling.b);
}
 */
void	free_texture(t_cub3d *cub3d)
{
	if (cub3d->map.texture_north)
		free(cub3d->map.texture_north);
	if (cub3d->map.texture_south)
		free(cub3d->map.texture_south);
	if (cub3d->map.texture_west)
		free(cub3d->map.texture_west);
	if (cub3d->map.texture_east)
		free(cub3d->map.texture_east);
}

int	read_file(t_cub3d **cub3d)
{
	if (map_status(cub3d) == -1)
		return (-1);
	if (check_map(cub3d) == -1)
	{
		free_texture(*cub3d);
		free_map_points(*cub3d);
		handle_error(ERO_MAP);
		return (-1);
	}
	if (setup_flood_fill(*cub3d) == -1)
	{
		free_texture(*cub3d);
		free_map_points(*cub3d);
		return (-1);
	}
	//free_texture(*cub3d);
	//free_map_points(*cub3d);
	printf("Parsing completed successfully.\n");
	return (0);
}

int	parsing_manager(t_cub3d **cub3d)
{
	if (open_file(cub3d) == -1)
		return (-1);
	if (read_file(cub3d) == -1)
		return (-1);
	return (0);
}
