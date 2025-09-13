/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/10 14:25:48 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_texture(t_data *d, char *path, t_tex *tex)
{
	if (!path)
		return (handle_error("Error\nTexture path is NULL"), 1);
	tex->img = mlx_xpm_file_to_image(d->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (handle_error("Error\nFailed to load XPM texture"), 1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (handle_error("Error\nmlx_get_data_addr failed (texture)"), 1);
	return (0);
}

int	init_textures(t_data *d)
{
	if (load_texture(d, d->c3d->map.texture_north, &d->tex[0]))
		return (1);
	if (load_texture(d, d->c3d->map.texture_south, &d->tex[1]))
		return (1);
	if (load_texture(d, d->c3d->map.texture_west, &d->tex[2]))
		return (1);
	if (load_texture(d, d->c3d->map.texture_east, &d->tex[3]))
		return (1);
	return (0);
}

void	destroy_textures(t_data *d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (d->tex[i].img)
			mlx_destroy_image(d->mlx, d->tex[i].img);
		d->tex[i].img = NULL;
		d->tex[i].addr = NULL;
		i++;
	}
}
