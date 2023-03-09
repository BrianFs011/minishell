/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:52:05 by briferre          #+#    #+#             */
/*   Updated: 2022/07/08 07:38:19 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_no;

	new_no = malloc(sizeof(t_list));
	if (!new_no)
		return (NULL);
	new_no->next = NULL;
	new_no->content = content;
	return (new_no);
}
