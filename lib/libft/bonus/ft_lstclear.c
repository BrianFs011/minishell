/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 08:18:44 by briferre          #+#    #+#             */
/*   Updated: 2022/07/08 08:58:39 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;
	t_list	*temp;

	if (!(*lst))
		return ;
	aux = (*lst);
	while (aux)
	{
		temp = aux;
		aux = aux->next;
		del(temp->content);
		free(temp);
	}
	(*lst) = NULL;
}
