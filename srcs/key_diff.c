/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:22:08 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"

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
