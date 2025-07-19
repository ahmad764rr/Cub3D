/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:24:46 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/10 18:20:32 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_error(char *_error)
{
	ft_putendl_fd(_error, 2);
}

void	handle_get_next_line(int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	open_file(t_cub3d **cub3d)
{
	(*cub3d)->fd = open((*cub3d)->file_path, O_RDONLY);
	if ((*cub3d)->fd < 0)
	{
		(*cub3d)->flag = 2;
		handle_error(ERO_OPEN_FILE);
		return (-1);
	}
	return (0);
}

int	open_file_manager(t_cub3d **cub3d)
{
	if (open_file(cub3d) == -1)
		return (-1);
	check_name((*cub3d));
	if ((*cub3d)->flag != 0)
		return (-1);
	return (0);
}

int	read_file_handle(t_cub3d **cub3d, char *line)
{
	handle_get_next_line((*cub3d)->fd, line);
	return (0);
}
