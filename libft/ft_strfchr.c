/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:57:04 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/20 17:24:38 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <string.h>

char	*ft_strfchr(const char *s, int c)
{
	char	cca;
	char	*temp;
	char	*copy;
	int		i;

	cca = (char)c;
	i = 0;
	copy = ft_strdup(s);
	if (!copy)
		return (NULL);
	temp = copy;
	while (*temp != '\0' && *temp != cca)
	{
		temp++;
		i++;
	}
	if (*temp != '\0' && *temp == cca && i > 0)
	{
		*temp = '\0';
		return (copy);
	}
	free(copy);
	return (NULL);
}

char	*ft_strmfchr(const char *s, const char *set)
{
	char	*copy;
	int		i;

	if (!s || !set)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (ft_strchr(set, s[i]) && i > 0)
			break ;
		i++;
	}
	if (i == 0 || s[0] == '\0')
		return (NULL);
	copy = (char *)malloc(i + 1);
	if (!copy)
		return (NULL);
	ft_strncpy(copy, s, i);
	copy[i] = '\0';
	return (copy);
}

/* #include <stdio.h>
int	main(void)
{
    char *inter = "ls here_doc.c < f< c< test.txt>d";
	//char	j[] = "abc";
	// char	k[] = "abcdcl";

	printf("THE VALUE IS: %s", ft_strfchr(inter, '<'));
	//printf("THE VALUE IS: %s", strchr(k, 'd'));
	//      printf("THE VALUE IS: %d \n",++d);
}
 */