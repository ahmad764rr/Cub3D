/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:08:22 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/10 18:25:29 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	comma_handle_color(char *line)
{
	char	*tmp;
	int		comma_count;

	comma_count = 0;
	tmp = line;
	while (ft_strchr(tmp, ','))
	{
		tmp = ft_strchr(tmp, ',');
		if (!tmp)
			break ;
		if (*(tmp + 1) == ',' || *(tmp + 1) == '\0')
			return (-1);
		comma_count++;
		tmp++;
	}
	if (comma_count != 2)
		return (-1);
	return (0);
}

int	find_std_color_formial(char *line, int *lock, int *index)
{
	int	i;

	i = *index;
	if (ft_isdigit(line[i]) && (*lock) == 0)
	{
		(*lock) = 1;
		while (ft_isdigit(line[i]))
			*index = ++i;
		return (1);
	}
	else if (line[i] == ',')
	{
		if ((*lock) == 0)
			return (-1);
		(*lock) = 0;
	}
	else if (ft_isdigit(line[i]) && (*lock) == 1)
		return (-1);
	else if (!ft_isspace(line[i]) && !ft_isdigit(line[i]) && line[i] != ',')
		return (-1);
	return (0);
}

int	handle_color_formality(char *line)
{
	int	i;
	int	ret;
	int	lock;

	i = 0;
	ret = 0;
	lock = 0;
	if (comma_handle_color(line) == -1)
		return (-1);
	while (line[i])
	{
		if (ft_isdigit(line[i]) || ft_isspace(line[i]) || line[i] == ',')
		{
			ret = find_std_color_formial(line, &lock, &i);
			if (ret == -1)
				return (-1);
			if (ret == 1)
				continue ;
		}
		else if ((line[i] != '+' && line[i] != '-') || !ft_isdigit(line[i + 1]))
			return (-1);
		i++;
	}
	return (0);
}
