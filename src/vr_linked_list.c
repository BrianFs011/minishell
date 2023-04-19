/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_linked_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:50:55 by briferre          #+#    #+#             */
/*   Updated: 2023/04/18 20:55:19 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	vr_insert(t_varlist **start, t_varlist var)
{
	t_varlist	*new_var;
	t_varlist	*temp;
	t_varlist	*before;

	temp = (*start);
	while (temp)
	{
		before = temp;
		temp = temp->next;
	}
	new_var = malloc(sizeof(t_varlist));
	new_var->name = ft_strcpy(var.name, TRUE);
	new_var->value = ft_strcpy(var.value, TRUE);
	new_var->size = 0;
	new_var->next = NULL;
	if (!(*start))
		(*start) = new_var;
	else
		before->next = new_var;
	(*start)->size++;
}

void	vr_update_insert(t_varlist **start, t_varlist var)
{
	t_varlist	*new_var;
	t_varlist	*temp;
	t_varlist	*before;

	temp = (*start);
	while (temp)
	{
		if (!ft_strcmp(temp->name, var.name))
		{
			temp->value = ft_strrpc(temp->value, var.value, TRUE, TRUE);
			return ;
		}
		before = temp;
		temp = temp->next;
	}
	new_var = malloc(sizeof(t_varlist));
	new_var->name = ft_strcpy(var.name, TRUE);
	new_var->value = ft_strcpy(var.value, TRUE);
	new_var->size = 0;
	new_var->next = NULL;
	if (!(*start))
		(*start) = new_var;
	else
		before->next = new_var;
	(*start)->size++;
}

t_string	vr_get_value(t_varlist *start, t_string name, t_bool empty)
{
	while (start)
	{
		if (!ft_strcmp(start->name, name))
			return (ft_strcpy(start->value, FALSE));
		start = start->next;
	}
	if (empty)
		return (ft_strcpy("", FALSE));
	return (ft_strcpy(name, FALSE));
}

t_bool	vr_change_value(t_varlist **start, t_varlist var)
{
	t_varlist	*temp;

	temp = (*start);
	while (temp)
	{
		if (!ft_strcmp(temp->name, var.name))
		{
			temp->value = ft_strrpc(temp->value, var.value, TRUE, FALSE);
			return (TRUE);
		}
		temp = temp->next;
	}
	return (FALSE);
}

void	vr_print(t_varlist *start)
{
	while (start)
	{
		printf("%s=%s\n", start->name, start->value);
		start = start->next;
	}
}

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
