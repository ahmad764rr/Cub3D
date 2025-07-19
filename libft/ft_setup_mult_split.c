/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_mult_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:09:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/23 13:40:30 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_break_char(char const *s, char c[], int size)
{
	int	j;

	while (*s)
	{
		j = 0;
		while (j < size)
		{
			if (*s == c[j])
				return ((char *)s);
			j++;
		}
		s++;
	}
	return ((char *)s);
}

int	word_mult_count(char const *s, char c[])
{
	int	i;
	int	size;
	int	j;

	i = 0;
	size = ft_strlen(c);
	while (*s)
	{
		j = 0;
		while (j < size && *s)
		{
			if (*s == c[j])
			{
				s++;
				j = 0;
			}
			else
				j++;
		}
		if (*s)
			i++;
		s = find_break_char(s, c, size);
	}
	return (i);
}

size_t	word_mult_len(char *s, char c[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
