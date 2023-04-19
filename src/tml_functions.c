/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:14:10 by briferre          #+#    #+#             */
/*   Updated: 2023/04/19 19:09:49 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		exit_status = bt_export(tml);
	if (!ft_strcmp(tml->split_cmd[0], "unset") && !tml->pp_cmd[1])
		if (!bt_unset(&tml->env_vars, tml->split_cmd[1]))
			exit_status = bt_unset(&tml->local_vars, tml->split_cmd[1]);
	if (ft_cc(tml->cmd, '=') && !tml->split_cmd[1] && !tml->pp_cmd[1])
		exit_status = vr_new_assignment(tml);
	if (exit_status != -1)
	{
		var.name = ft_strcpy("status", FALSE);
		var.value = ft_strcpy(ft_itoa(exit_status), TRUE);
		vr_insert(&tml->pid_list, var);
	}
	return (exit_status);
}

static t_bool	condition_for_find_exec(t_ml *tml)
{
	return (!((!ft_strncmp(tml->split_cmd[0], "./", 2))
			|| tml->split_cmd[0][0] == '/')
			&& !ft_cc(tml->split_cmd[0], '=')
			&& ft_strcmp(tml->split_cmd[0], "exit")
			&& ft_strcmp(tml->split_cmd[0], "cd")
			&& ft_strcmp(tml->split_cmd[0], "echo")
			&& ft_strcmp(tml->split_cmd[0], "pwd")
			&& ft_strcmp(tml->split_cmd[0], "env")
			&& ft_strcmp(tml->split_cmd[0], "export")
			&& ft_strcmp(tml->split_cmd[0], "unset")
		);
}

static t_bool	condition_for_exit(t_ml *tml)
{
	// printf("condition exit: %d\n", g_pid);
	return (!ft_strcmp(tml->split_cmd[0], "exit")
		|| !ft_strcmp(tml->split_cmd[0], "cd")
		|| !ft_strcmp(tml->split_cmd[0], "export")
		|| !ft_strcmp(tml->split_cmd[0], "unset")
		|| !ft_strcmp(tml->split_cmd[0], "echo")
		|| !ft_strcmp(tml->split_cmd[0], "pwd")
		|| !ft_strcmp(tml->split_cmd[0], "env")
		|| ft_cc(tml->split_cmd[0], '=')
		|| g_pid == -1
	);
}

int	tml_exec_child(t_ml *tml, int *fd)
{
	int			exit_status;
	t_string	*env_updated;

	exit_status = 0;
	exit_status = rd_redirection(tml, fd);
	if (condition_for_find_exec(tml) && exit_status == 0)
		exit_status = tml_find_exec(tml);
	if (tml->pp_quant != 0 && exit_status == 0)
		pp_switch(tml);
	if (!ft_strcmp(tml->split_cmd[0], "pwd") && exit_status == 0)
		exit_status = bt_pwd(tml);
	if (!ft_strcmp(tml->split_cmd[0], "echo") && exit_status == 0)
	{
		exit_status = bt_echo(tml->split_cmd);
		exit_status = tml->exit_status;
	}
	if (!ft_strcmp(tml->split_cmd[0], "env") && exit_status == 0)
		exit_status = bt_env(tml->env_vars);
	if (condition_for_exit(tml) || exit_status != 0)
		exit(exit_status);
	env_updated = tml_construct_env(tml);
	if (execve(tml->split_cmd[0], tml->split_cmd, env_updated) == -1)
	{
		perror("Execve");
		tml_free_sprt_cmd(env_updated);
		tml->running = EXIT_SILENCED;
		exit_status = 1;
	}
	return (exit_status);
}
