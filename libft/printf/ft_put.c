/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:12:46 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/29 20:00:49 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printchar(char c, int *flag)
{
	write((*flag), &c, 1);
}

static int	getlength(long long num)
{
	int	i;

	i = 0;
	if (num <= 0)
	{
		i++;
		num *= -1;
	}
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

int	ft_putstr(char *str, int *flag)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			write((*flag), &str[i], 1);
			i++;
		}
	}
	else
	{
		return (ft_putstr("(null)", flag));
	}
	return (i);
}

int	ft_putnbr(long nb, int *flag)
{
	int	neg;

	neg = 0;
	if (nb < 0)
	{
		ft_printchar('-', flag);
		nb *= -1;
		neg++;
	}
	if (nb >= 10)
	{
		ft_putnbr((nb / 10), flag);
		ft_printchar(((nb % 10) + 48), flag);
	}
	else
		ft_printchar((nb + 48), flag);
	return (neg + getlength(nb));
}

int	ft_putunbr(unsigned int nb, int *flag)
{
	if (nb >= 10)
	{
		ft_putunbr((nb / 10), flag);
		ft_printchar(((nb % 10) + '0'), flag);
	}
	else
		ft_printchar((nb + 48), flag);
	return (getlength(nb));
}
/* 
int	main(void){
  printf("%d",printf("\n%d",0));
} */
