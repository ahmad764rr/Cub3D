/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovl_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:17:05 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/overlay.h"
#include <math.h>

int	key_press(int kc, t_data *d)
{
	if (is_key_esc(kc))
		exit(0);
	if (is_key_w(kc) || is_key_up(kc))
		d->act_fwd = 1;
	if (is_key_s(kc) || is_key_down(kc))
		d->act_back = 1;
	if (is_key_a(kc))
		d->act_left = 1;
	if (is_key_d(kc))
		d->act_right = 1;
	if (is_key_left(kc))
		d->act_turn_l = 1;
	if (is_key_right(kc))
		d->act_turn_r = 1;
	if (is_key_r(kc))
		d->look_up = 1;
	if (is_key_f(kc))
		d->look_down = 1;
	return (0);
}

int	key_release(int kc, t_data *d)
{
	if (is_key_w(kc) || is_key_up(kc))
		d->act_fwd = 0;
	if (is_key_s(kc) || is_key_down(kc))
		d->act_back = 0;
	if (is_key_a(kc))
		d->act_left = 0;
	if (is_key_d(kc))
		d->act_right = 0;
	if (is_key_left(kc))
		d->act_turn_l = 0;
	if (is_key_right(kc))
		d->act_turn_r = 0;
	if (is_key_r(kc))
		d->look_up = 0;
	if (is_key_f(kc))
		d->look_down = 0;
	return (0);
}

int	close_game(t_data *d)
{
	(void)d;
	exit(0);
	return (0);
}
