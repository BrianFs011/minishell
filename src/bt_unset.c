/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:37:39 by briferre          #+#    #+#             */
/*   Updated: 2023/04/21 17:23:07 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
			return (0);
		}
		before = temp;
		temp = temp->next;
	}
	return (0);
}
