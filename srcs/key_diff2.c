/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_diff2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:44:01 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:44:07 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_key_up(int kc)
{
	if (kc == 111 || kc == 65362 || kc == 126)
		return (1);
	return (0);
}

int	is_key_down(int kc)
{
	if (kc == 116 || kc == 65364 || kc == 125)
		return (1);
	return (0);
}

int	is_key_esc(int kc)
{
	if (kc == 65307 || kc == 53)
		return (1);
	return (0);
}

int	is_key_r(int kc)
{
	if (kc == 27 || kc == 114 || kc == 15)
		return (1);
	return (0);
}

int	is_key_f(int kc)
{
	if (kc == 41 || kc == 102 || kc == 3)
		return (1);
	return (0);
}
