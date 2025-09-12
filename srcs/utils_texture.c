/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:40:00 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/12 10:48:08 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
