/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_linked_list_delete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:46:28 by briferre          #+#    #+#             */
/*   Updated: 2023/04/25 20:59:39 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	vr_delete(t_varlist **start)
{
	t_varlist	*temp;

	while ((*start))
	{
		temp = (*start);
		(*start) = (*start)->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

t_bool	vr_delete_node(t_varlist **start, t_varlist var)
{
	t_varlist	*temp;
	t_varlist	*before;
	t_bool		finded;

	temp = (*start);
	before = NULL;
	finded = FALSE;
	while (temp)
	{
		before = temp;
		finded = !strcmp(temp->name, var.name);
		if (finded)
			break ;
		temp = temp->next;
	}
	if (!before)
	{
		free((*start));
		(*start) = NULL;
	}
	else if (finded)
	{
		temp = temp->next;
		free(before->next);
		before->next = temp;
	}
	return (finded);
}
