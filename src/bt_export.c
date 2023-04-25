/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:39:31 by briferre          #+#    #+#             */
/*   Updated: 2023/04/25 19:19:36 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_export(t_ml *tml)
{
	t_varlist	var;
	int			exit_status;

	exit_status = 0;
	var = vr_get_name_value(tml->split_cmd[1]);
	if (!ft_strisalpha(var.name) || !*var.name)
	{
		ft_print_error(ft_strjoin("export: `", tml->split_cmd[1]),
			"': not a valid identifier", TRUE);
		free(var.name);
		free(var.value);
		return (1);
	}
	if (ft_cc(tml->cmd, '='))//checa se: export teste=10
	{
		if (!vr_change_value(&(tml->env_vars), var))
			vr_insert(&(tml->env_vars), var, FALSE, FALSE);
		free(var.name);
		free(var.value);
	}
	else //se: export teste
		exit_status = export_from_local_vars(tml);
	return (exit_status);
}
