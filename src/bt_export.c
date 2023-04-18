/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:39:31 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 20:37:14 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_export(t_ml *tml)
{
	t_varlist	var;
	int			exit_status;

	exit_status = 0;
	if (ft_cc(tml->cmd, '='))
	{
		var = vr_get_name_value(tml->split_cmd[1]);
		if (!ft_strisalpha(var.name))
		{
			free(var.name);
			free(var.value);
			return (1);
		}
		if (!vr_change_value(&(tml->env_vars), var))
			vr_insert(&(tml->env_vars), var);
		else
		{
			free(var.name);
			free(var.value);
		}
	}
	else
		exit_status = export_from_local_vars(tml);
	// vr_print(tml->local_vars);
	return (exit_status);
}
