/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_unset_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:40:08 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 08:11:30 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	remove_no(t_varlist **start, t_varlist **temp, t_varlist **before)
{
	t_varlist	*aux;

	if ((*before))
	{
		aux = (*temp);
		(*before)->next = (*temp)->next;
		free(aux->name);
		free(aux->value);
		free(aux);
	}
	else
	{
		free((*start)->name);
		free((*start)->value);
		free((*start));
		(*start) = NULL;
	}
}

int	export_from_assigned(t_ml *tml)
{
	t_varlist	*temp;
	t_varlist	*before;

	before = NULL;
	temp = tml->assigned;
	if (!ft_strisalpha(tml->sprt_cmd[1]))
		return (1);
	while (temp)
	{
		if (!ft_strcmp(temp->name, tml->sprt_cmd[1]))
		{
			vr_insert(&(tml->vars), *temp);
			remove_no(&(tml->assigned), &temp, &before);
			break ;
		}
		before = temp;
		temp = temp->next;
	}
	return (0);
}
