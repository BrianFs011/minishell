/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_builtins02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:36:39 by briferre          #+#    #+#             */
/*   Updated: 2023/04/05 16:59:12 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	remove_no(t_varlist **start, t_varlist **temp, t_varlist **before)
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

static int	export_from_assigned(t_ml *tml)
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

int	bt_export(t_ml *tml)
{
	t_varlist	var;
	int			exit_status;

	exit_status = 0;
	if (ft_cc(tml->cmd, '='))
	{
		var = vr_get_name_value(tml->sprt_cmd[1]);
		if (!ft_strisalpha(var.name))
		{
			free(var.name);
			free(var.value);
			return (1);
		}
		if (!vr_change_value(&(tml->vars), var))
			vr_insert(&(tml->vars), var);
		else
		{
			free(var.name);
			free(var.value);
		}
	}
	else
		exit_status = export_from_assigned(tml);
	vr_print(tml->assigned);
	return (exit_status);
}

t_bool	bt_unset(t_varlist **start, t_string string)
{
	t_varlist	*temp;
	t_varlist	*before;

	temp = (*start);
	before = NULL;
	while (temp)
	{
		if (!ft_strcmp(temp->name, string))
		{
			remove_no(start, &temp, &before);
			return (TRUE);
		}
		before = temp;
		temp = temp->next;
	}
	return (FALSE);
}

int	bt_env(t_varlist *start)
{
	vr_print(start);
	return (0);
}
