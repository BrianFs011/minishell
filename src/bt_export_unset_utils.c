/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_unset_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:40:08 by briferre          #+#    #+#             */
/*   Updated: 2023/04/21 17:54:20 by sde-cama         ###   ########.fr       */
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
		(*start) = (*temp)->next;
		free((*temp)->name);
		free((*temp)->value);
		free((*temp));
	}
}

int	export_from_local_vars(t_ml *tml)
{
	t_varlist	*temp;
	t_varlist	*before;

	before = NULL;
	temp = tml->local_vars;
	if (!ft_strisalpha(tml->split_cmd[1]))
		return (1);
	while (temp)
	{
		if (!ft_strcmp(temp->name, tml->split_cmd[1]))
		{
			vr_update_insert(&(tml->env_vars), *temp);
			remove_no(&(tml->local_vars), &temp, &before);
			break ;
		}
		before = temp;
		temp = temp->next;
	}
	return (0);
}
