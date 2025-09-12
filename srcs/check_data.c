/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:03:17 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/02 16:55:23 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_color_data(char *line, int skip, t_cub3d **cub3d)
{
	int		i;
	char	*trimmed_line;

	i = skip;
	while (ft_isspace(line[i]))
		i++;
	trimmed_line = ft_strchr(line + skip, line[i]);
	if (!trimmed_line)
	{
		handle_error(ERO_MAP);
		return (-1);
	}
	if (handle_color_formality(trimmed_line) == -1)
	{
		handle_error(ERO_MAP);
		return (-1);
	}
	if (check_values(trimmed_line, cub3d, line[0]) == -1)
	{
		handle_error(ERO_MAP);
		return (-1);
	}
	return (0);
}

void	check_data_error(t_cub3d **cub3d, char *message, int flag)
{
	(*cub3d)->flag = flag;
	if (message)
		handle_error(message);
}

int	check_data_condition_2(char *trimmed_line, t_cub3d **cub3d,
		int *is_complete, int *height)
{
	if (ft_strncmp(trimmed_line, "F ", 2) == 0 || ft_strncmp(trimmed_line, "C ",
			2) == 0)
	{
		(*is_complete)++;
		if (handle_color_data(trimmed_line, 2, cub3d) == -1)
			return (-1);
	}
	else if ((ft_strncmp(trimmed_line, "1", 1) == 0 || ft_strncmp(trimmed_line,
				"0", 1) == 0 || ft_strncmp(trimmed_line, " ", 1) == 0))
	{
		(*height)++;
		if ((*is_complete) < 6 && (ft_strncmp(trimmed_line, "1", 1) == 0
				|| ft_strncmp(trimmed_line, "0", 1) == 0
				|| ft_strncmp(trimmed_line, " ", 1) == 0))
		{
			check_data_error(cub3d, ERO_MAP, 6);
			return (-1);
		}
	}
	else
	{
		check_data_error(cub3d, ERO_MAP, 6);
		return (-1);
	}
	return (0);
}

int	check_data_condition(char *trimmed_line, t_cub3d **cub3d, int *is_complete)
{
	int	height;

	height = 0;
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
			"SO ", 3) == 0 || ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
	{
		(*is_complete)++;
		if (is_acceptable_file(trimmed_line, 3, cub3d) == -1)
			return (-1);
	}
	else if (check_data_condition_2(trimmed_line, cub3d, is_complete,
			&height) == -1)
		return (-1);
	if ((*cub3d)->map.map_height == -1 && height > 0)
		(*cub3d)->map.map_height = 0;
	(*cub3d)->map.map_height += height;
	return (0);
}

int	setup_check_data(char *line, t_cub3d **cub3d, int *is_complete)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
	{
		handle_error(ERO_MALLOC);
		return (-1);
	}
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		check_data_error(cub3d, NULL, 6);
		return (0);
	}
	if (check_data_condition(trimmed_line, cub3d, is_complete) == -1)
	{
		free(trimmed_line);
		return (-1);
	}
	free(trimmed_line);
	return (0);
}
