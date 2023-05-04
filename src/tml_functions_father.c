/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions_father.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:14:10 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 19:18:43 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	export_condition(t_ml *tml)
{
	return (
		tml->split_cmd[1] && ft_strcmp(tml->split_cmd[1], ">>")
		&& ft_strcmp(tml->split_cmd[1], ">")
		&& ft_strcmp(tml->split_cmd[1], "<")
		&& ft_strcmp(tml->split_cmd[1], "<<")
	);
}

int	tml_exec_father(t_ml *tml)
{
	int			exit_status;
	t_varlist	var;

	exit_status = -1;
	if (!ft_strcmp(tml->split_cmd[0], "exit") && !ft_cc(tml->cmd, '|'))
		exit_status = bt_exit(tml);
	if (!ft_strcmp(tml->split_cmd[0], "cd"))
		exit_status = bt_cd(tml);
	if (!ft_strcmp(tml->split_cmd[0], "export") && !tml->pp_cmd[1])
		if (export_condition(tml))
			exit_status = bt_export(tml);
	if (!ft_strcmp(tml->split_cmd[0], "unset") && !tml->pp_cmd[1])
	{
		exit_status = bt_unset(&tml->env_vars, tml->split_cmd[1]);
		exit_status = bt_unset(&tml->local_vars, tml->split_cmd[1]);
	}
	if (ft_cc(tml->cmd, '=') && !tml->split_cmd[1] && !tml->pp_cmd[1])
		exit_status = vr_new_assignment(tml);
	if (exit_status != -1)
	{
		var.name = ft_strcpy("status", FALSE);
		var.value = ft_strcpy(ft_itoa(exit_status), TRUE);
		vr_insert(&tml->pid_list, var, TRUE, TRUE);
	}
	return (exit_status);
}
