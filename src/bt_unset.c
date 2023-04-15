/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:37:39 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 07:38:24 by briferre         ###   ########.fr       */
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
			return (TRUE);
		}
		before = temp;
		temp = temp->next;
	}
	return (FALSE);
}
