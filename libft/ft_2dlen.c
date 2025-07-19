/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:51:57 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/06 14:00:31 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_2dlen(char **str)
{
	int		counter;

	while (!str)
		return (0);
	counter = 0;
	while (str[counter] != NULL)
		counter++;
	return (counter);
}
