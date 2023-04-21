/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_local_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:49:39 by briferre          #+#    #+#             */
/*   Updated: 2023/04/18 20:54:32 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	vr_new_assignment(t_ml *tml)
{
	t_varlist	var;

	var = vr_get_name_value(tml->split_cmd[0]);
	if (!ft_strisalpha(var.name))
		return (127);
	if (!vr_change_value(&(tml->env_vars), var))
	{
		if (!vr_change_value(&(tml->local_vars), var))
			vr_update_insert(&(tml->local_vars), var);
		else
		{
			free(var.name);
			free(var.value);
		}
	}
	return (0);
}
