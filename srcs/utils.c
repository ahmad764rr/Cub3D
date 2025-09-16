/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:00:04 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/14 20:50:29 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	check_name(t_cub3d *cub3d)
{
	int		fd;
	char	*arg;
	int		i;

	i = 0;
	arg = cub3d->file_path;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		cub3d->flag = 15;
		handle_error(ERO_FILE);
		return ;
	}
	else
		close(fd);
	while (arg[i])
		i++;
	if (arg[i - 1] != 'b' || arg[i - 2] != 'u' || arg[i - 3] != 'c' || arg[i
			- 4] != '.')
	{
		cub3d->flag = 1;
		close(cub3d->fd);
		handle_error(ERO_NAME_FILE);
		return ;
	}
}

int	check_access(char *line)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
	{
		handle_error(ERO_MALLOC);
		return (-1);
	}
	ret = open(trimmed, O_RDONLY);
	if (ret == -1)
		handle_error(ERO_FILE);
	else
		close(ret);
	free(trimmed);
	if (ret == -1)
		return (-1);
	return (0);
}
