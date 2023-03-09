/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_linked_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:50:55 by briferre          #+#    #+#             */
/*   Updated: 2023/03/07 15:17:33 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	vr_insert(t_vars **start, t_vars var)
{
	t_vars	*new_var;
	t_vars	*temp;
	t_vars	*before;

	temp = (*start);
	while (temp)
	{
		if (!ft_strcmp(temp->name, var.name))
		{
			free(temp->value);
			temp->value = ft_strcpy(var.value, TRUE);
			return ;
		}
		before = temp;
		temp = temp->next;
	}
	new_var = malloc(sizeof(t_vars));
	new_var->name = ft_strcpy(var.name, TRUE);
	new_var->value = ft_strcpy(var.value, TRUE);
	new_var->next = NULL;
	if (!(*start))
		(*start) = new_var;
	else
		before->next = new_var;
}

t_string	vr_get_var(t_vars *start, t_string name)
{
	while (start)
	{
		if (!ft_strcmp(start->name, name))
			return (ft_strcpy(start->value, FALSE));
		start = start->next;
	}
	return (ft_strcpy("", FALSE));
}

void	vr_print(t_vars *start)
{
	while (start)
	{
		printf("%s=%s\n", start->name, start->value);
		start = start->next;
	}
}

void	vr_delete(t_vars **start)
{
	t_vars	*temp;

	while ((*start))
	{
		temp = (*start);
		(*start) = (*start)->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
