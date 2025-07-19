/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:06:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 01:30:45 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
size_t				ft_strlen(const char *s);
size_t				word_mult_len(char *s, char c[]);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
long long			ft_mod(long long a, long long b);
long long			ft_atoi_long(const char *str);
int					ft_abs(int __x);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					hexa_to_int(char *s);
int					ft_atoi_hexa(char s);
int					ft_2dlen(char **str);
int					ft_lstsize(t_list *lst);
int					ft_atoi(const char *str);
int					ft_power(int num, int power);
int					ft_strcmp(char *s1, char *s2);
int					word_mult_count(char const *s, char c[]);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_itoa(int n);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strfchr(const char *s, int c);
char				**ft_split(char const *s, char c);
char				*ft_strmchr(const char *s, char c[]);
char				**ft_mult_split(char const *s, char c[]);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmchr_noqoute(const char *s, char c[]);
char				*ft_strmfchr(const char *s, const char *set);
char				*ft_strrmchr(const char *s, const char *set);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				frees_split(char **root);
void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				*ft_calloc(size_t n, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_strncpy(char *dest, const char *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				insertend(t_list **root, void *new_value, int *flag);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
#endif
