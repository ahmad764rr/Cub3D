/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:40:00 by ahramada          #+#    #+#             */
/*   Updated: 2025/09/10 14:45:24 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	has_extension(const char *path, const char *ext)
{
	size_t	lp;
	size_t	le;

	if (!path || !ext)
		return (0);
	lp = ft_strlen(path);
	le = ft_strlen(ext);
	if (lp < le)
		return (0);
	return (ft_strncmp(path + (lp - le), ext, le) == 0);
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

/*
** Validate a texture file path:
** - skip whitespace
** - ensure .xpm extension
** - check file is readable
*/
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
	if (!has_extension(trimmed_line, ".xpm"))
	{
		handle_error("Error\nTexture must be an .xpm file");
		return (-1);
	}
	set_texture_data(line, skip, cub3d);
	if (check_access(trimmed_line) == -1)
		return (-1);
	return (0);
}
