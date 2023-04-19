/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:39:31 by briferre          #+#    #+#             */
/*   Updated: 2023/04/19 19:26:05 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_export(t_ml *tml)
{
	t_varlist	var;
	int			exit_status;

	exit_status = 0;
	var = vr_get_name_value(tml->split_cmd[1]);
	if (!ft_strisalpha(var.name))
	{
		// dup(STDERR_FILENO);
		// printf(" not a valid identifier\n");
		// dup(STDOUT_FILENO);
		write(STDERR_FILENO, " not a valid identifier\n", 25);
		free(var.name);
		free(var.value);
		return (1);
	}
	if (ft_cc(tml->cmd, '='))
	{
		if (!vr_change_value(&(tml->env_vars), var))
			vr_update_insert(&(tml->env_vars), var);
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
