/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:39:31 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 17:04:48 by briferre         ###   ########.fr       */
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
	// vr_print(tml->assigned);
	return (exit_status);
}
