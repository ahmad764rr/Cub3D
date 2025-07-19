/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:59:07 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/07 17:45:33 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrmchr(const char *s, const char *set)
{
	int	i;
	int	j;

	if (!s || !set)
		return (NULL);
	i = ft_strlen(s);
	while (i--)
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				return ((char *)(s + i));
			j++;
		}
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*st;
	size_t			i;
	size_t			i1;

	st = (unsigned char *)s;
	i = (ft_strlen((char *)st));
	i1 = i;
	while (i)
	{
		i--;
		st++;
	}
	if ((char)c == '\0')
		return ((char *)st);
	while (i1 && st)
	{
		st--;
		--i1;
		if (*st == (char)c)
			return ((char *)st);
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

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

int	main(void)
{
	//char	j[] = "123456789";
	char	k[] = "abfbonjour";

	printf("THE VALUE IS: %s\n", ft_strrchr(k, 'a'));
	printf("THE VALUE IS: %s", strrchr(k, 'a'));
	}
*/
