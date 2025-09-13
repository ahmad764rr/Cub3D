/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_diff3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:44:27 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:44:34 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_key_d(int kc)
{
	if (kc == 40 || kc == 100 || kc == 2)
		return (1);
	return (0);
}

int	is_key_left(int kc)
{
	if (kc == 113 || kc == 65361 || kc == 123)
		return (1);
	return (0);
}

int	is_key_right(int kc)
{
	if (kc == 114 || kc == 65363 || kc == 124)
		return (1);
	return (0);
}
