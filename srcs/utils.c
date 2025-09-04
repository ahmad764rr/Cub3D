/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:00:04 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/02 16:55:08 by ahramada         ###   ########.fr       */
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
	char	*arg;
	int		i;

	i = 0;
	arg = cub3d->file_path;
	if (access(arg, F_OK | R_OK) == -1)
	{
		cub3d->flag = 15;
		handle_error(ERO_FILE);
		return ;
	}
	while (arg[i])
		i++;
	if (arg[i - 1] != 'b' || arg[i - 2] != 'u' || arg[i - 3] != 'c'
		|| arg[i - 4] != '.')
	{
		cub3d->flag = 1;
		handle_error(ERO_NAME_FILE);
		return ;
	}
}

int	check_access(char *line)
{
	if (access(line, F_OK | R_OK | X_OK) == -1)
	{
		handle_error(ERO_FILE);
		return (-1);
	}
	return (0);
}

char	*valid_set_texture_data(char *line, char *prefix)
{
	if (line == NULL && prefix == NULL)
	{
		handle_error(ERO_MAP);
		return (NULL);
	}
	if (line == NULL)
		return (ft_strdup(prefix));
	free(line);
	return (ft_strdup(prefix));
}

int	is_acceptable_file(char *line, int skip, t_cub3d **cub3d)
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
		return (-1);
	}
	set_texture_data(line, skip, cub3d);
	if (check_access(trimmed_line) == -1)
		return (-1);
	return (0);
}
