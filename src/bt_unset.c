/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:37:39 by briferre          #+#    #+#             */
/*   Updated: 2023/04/21 17:58:30 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_unset(t_varlist **start, t_string string)
{
	t_varlist	*temp;
	t_varlist	*before;
	// t_string	a;

	// a = ft_strcpy("", TRUE);
	// printf("%s", a);
	// free(a);
	if (!string)
		return (0);
	temp = (*start);
	before = NULL;
	while (temp)
	{
		if (!ft_strcmp(temp->name, string))
		{
			remove_no(start, &temp, &before);
			// return (0);
		}
		before = temp;
		temp = temp->next;
	}
	return (0);
}
