/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:14:10 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 10:07:15 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	tml_exec_father(t_ml *tml)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp(tml->sprt_cmd[0], "exit") && !ft_cc(tml->cmd, '|'))
		exit_status = bt_exit(tml);
	if (!ft_strcmp(tml->sprt_cmd[0], "cd"))
		exit_status = bt_cd(tml);
	if (!ft_strcmp(tml->sprt_cmd[0], "export") && !tml->pp_cmd[1])
		exit_status = bt_export(tml);
	if (!ft_strcmp(tml->sprt_cmd[0], "unset") && !tml->pp_cmd[1])
		if (!bt_unset(&tml->vars, tml->sprt_cmd[1]))
			exit_status = bt_unset(&tml->assigned, tml->sprt_cmd[1]);
	if (ft_cc(tml->cmd, '=') && !tml->sprt_cmd[1] && !tml->pp_cmd[1])
		exit_status = vr_new_assignment(tml);
	return (exit_status);
}

static t_bool	condition_for_find_exec(t_ml *tml)
{
	return (!((!ft_strncmp(tml->sprt_cmd[0], "./", 2))
			|| tml->sprt_cmd[0][0] == '/')
			&& !ft_cc(tml->sprt_cmd[0], '=')
			&& ft_strcmp(tml->sprt_cmd[0], "exit")
			&& ft_strcmp(tml->sprt_cmd[0], "cd")
			&& ft_strcmp(tml->sprt_cmd[0], "echo")
			&& ft_strcmp(tml->sprt_cmd[0], "pwd")
			&& ft_strcmp(tml->sprt_cmd[0], "env")
			&& ft_strcmp(tml->sprt_cmd[0], "export")
			&& ft_strcmp(tml->sprt_cmd[0], "unset")
		);
}

static t_bool	condition_for_exit(t_ml *tml)
{
	// printf("condition exit: %d\n", g_pid);
	return (!ft_strcmp(tml->sprt_cmd[0], "exit")
		|| !ft_strcmp(tml->sprt_cmd[0], "cd")
		|| !ft_strcmp(tml->sprt_cmd[0], "export")
		|| !ft_strcmp(tml->sprt_cmd[0], "unset")
		|| !ft_strcmp(tml->sprt_cmd[0], "echo")
		|| !ft_strcmp(tml->sprt_cmd[0], "pwd")
		|| !ft_strcmp(tml->sprt_cmd[0], "env")
		|| ft_cc(tml->sprt_cmd[0], '=')
		|| g_pid == -1
	);
}

int	tml_exec_child(t_ml *tml, int *fd)
{
	int	exit_status;

	exit_status = 0;
	exit_status = rd_redirection(tml, fd);
	if (condition_for_find_exec(tml) && exit_status == 0)
		exit_status = tml_find_exec(tml);
	if (tml->pp_quant != 0 && exit_status == 0)
		pp_switch(tml);
	if (!ft_strcmp(tml->sprt_cmd[0], "pwd") && exit_status == 0)
		exit_status = bt_pwd(tml);
	if (!ft_strcmp(tml->sprt_cmd[0], "echo") && exit_status == 0)
		exit_status = bt_echo(tml->sprt_cmd);
	if (!ft_strcmp(tml->sprt_cmd[0], "env") && exit_status == 0)
		exit_status = bt_env(tml->vars);
	if (condition_for_exit(tml) || exit_status != 0)
		exit(exit_status);
	tml->env = tml_construct_env(tml);
	// printf("%d\n", exit_status);
	if (execve(tml->sprt_cmd[0], tml->sprt_cmd, tml->env) == -1)
	{
		perror("Execve");
		tml->running = EXIT_SILENCED;
		exit_status = 1;
	}
	return (exit_status);
}
