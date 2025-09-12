/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:00:04 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/12 10:43:28 by ahramada         ###   ########.fr       */
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
	if (arg[i - 1] != 'b' || arg[i - 2] != 'u' || arg[i - 3] != 'c' || arg[i
		- 4] != '.')
	{
		cub3d->flag = 1;
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
	ret = access(trimmed, F_OK | R_OK);
	if (ret == -1)
		handle_error(ERO_FILE);
	free(trimmed);
	if (ret == -1)
		return (-1);
	return (0);
}
