/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:03:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 15:44:35 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmchr(const char *s, char c[])
{
	int		i;

	while (*s != '\0')
	{
		i = 0;
		while (c[i] != '\0')
		{
			if (*s == c[i])
				return ((char *)s);
			i++;
		}
		s++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	cca;

	cca = (char)c;
	while (*s != '\0' && *s != cca)
		s++;
	if (*s == cca)
		return ((char *)s);
	return (NULL);
}
/* 
#include <stdio.h>
int	main(void)
{
	char	j[] = "<>";
	char	k[] = "abc<dc>l";
	char	t[] = "abcdefg";
	char	*temp;

	temp = ft_strmchr(k, j); // i could set it as "<>" or "><"
	printf("THE VALUE IS: %s\n", temp); // output: <dc>l

	temp = ft_strmchr(temp + 1, j);
	printf("THE VALUE IS: %s\n", temp); // output: >l

	temp = ft_strmchr(temp + 1, j);
	printf("THE VALUE IS: %s\n", temp);// output: NULL

	printf("THE VALUE IS: %s", ft_strchr(t, 'd'));//output: defg 
}
 */