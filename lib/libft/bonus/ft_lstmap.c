/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:11:15 by briferre          #+#    #+#             */
/*   Updated: 2022/07/08 10:25:23 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;

	start = NULL;
	while (lst)
	{
		ft_lstadd_back(&start, ft_lstnew(f(lst->content)));
		if (!start)
		{
			ft_lstdelone(start, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (start);
}
