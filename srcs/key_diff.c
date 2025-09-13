/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 17:44:31 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_key_w(int kc)
{
	if (kc == 25 || kc == 119 || kc == 13)
		return (1);
	return (0);
}

int	is_key_s(int kc)
{
	if (kc == 39 || kc == 115 || kc == 1)
		return (1);
	return (0);
}

int	is_key_a(int kc)
{
	if (kc == 38 || kc == 97 || kc == 0)
		return (1);
	return (0);
}
