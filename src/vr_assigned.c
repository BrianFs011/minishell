/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_assigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:49:39 by briferre          #+#    #+#             */
/*   Updated: 2023/04/05 10:43:13 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	vr_new_assignment(t_ml *tml)
{
	t_varlist	var;

	var = vr_get_name_value(tml->sprt_cmd[0]);
	if (!ft_strisalpha(var.name))
		return (127);
	if (!vr_change_value(&(tml->vars), var))
	{
		if (!vr_change_value(&(tml->assigned), var))
			vr_insert(&(tml->assigned), var);
		else
		{
			free(var.name);
			free(var.value);
		}
	}
	return (0);
}
