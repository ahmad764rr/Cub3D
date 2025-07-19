/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:50:47 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/08 18:09:00 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	char	*len;

	i = 0;
	len = (char *)s;
	while (len[i++] != '\0')
		;
	return (i - 1);
}
/*#include <stdio.h>
int main(){
printf("%ld", ft_strlen("adsff"));
}*/
