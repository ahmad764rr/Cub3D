/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:59:36 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/29 20:00:47 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

void	ft_printchar(char c, int *flag);
int		ft_putnbr(long nb, int *flag);
int		ft_putchar1(char c, int *flag);
int		ft_putstr(char *str, int *flag);
int		ft_print_ptr(unsigned long ptr, int *flag);
int		ft_putunbr(unsigned int nb, int *flag);
int		ft_tohexa(unsigned long nb, char type, int *flag);
int		getlength_hexa(long num);
int		nq_conversion(char a, va_list args, int *flag);
int		ft_printf(const char *num, ...);

#endif
