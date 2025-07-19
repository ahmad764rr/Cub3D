/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_to_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:00:50 by nqasem            #+#    #+#             */
/*   Updated: 2025/03/17 16:01:35 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hexa_to_int(char *s)
{
	int	hexa;
	int	size;
	int	base;
	int	i;

	i = 0;
	hexa = 0;
	base = 16;
	size = ft_strlen(s);
	while (i < size)
	{
		hexa += ft_power(base, (size - 1) - i) * ft_atoi_hexa(s[i]);
		i++;
	}
	return (hexa);
}
