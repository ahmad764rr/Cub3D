/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:27:15 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/15 19:20:17 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insertend(t_list **root, void *new_value, int *flag)
{
	t_list	*new_node;
	t_list	*curr;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		*flag = 12;
	if (*flag == 12)
		return ;
	new_node->content = ft_strdup(new_value);
	if (new_node->content == NULL)
	{
		free(new_node);
		*flag = 12;
		return ;
	}
	new_node->next = NULL;
	if (*root == NULL)
	{
		(*root) = new_node;
		return ;
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}
