/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:14:10 by briferre          #+#    #+#             */
/*   Updated: 2023/05/06 23:12:43 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_bool	condition_for_find_exec(t_ml *tml)
{
	return (!(
			(!ft_strncmp(tml->split_cmd[0], "./", 2))
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
	return (!ft_strcmp(tml->split_cmd[0], "exit")
		|| !ft_strcmp(tml->split_cmd[0], "cd")
		|| !ft_strcmp(tml->split_cmd[0], "export")
		|| !ft_strcmp(tml->split_cmd[0], "unset")
		|| !ft_strcmp(tml->split_cmd[0], "echo")
		|| !ft_strcmp(tml->split_cmd[0], "pwd")
		|| !ft_strcmp(tml->split_cmd[0], "env")
		|| ft_cc(tml->split_cmd[0], '=')
	);
}

static int	exec_builtins(t_ml *tml, int exit_status)
{
	if (!ft_strcmp(tml->split_cmd[0], "export") && !tml->split_cmd[1])
		exit_status = bt_print_export(tml->env_vars);
	if (!ft_strcmp(tml->split_cmd[0], "pwd") && exit_status == 0)
		exit_status = bt_pwd(tml);
	if (!ft_strcmp(tml->split_cmd[0], "echo") && exit_status == 0)
		exit_status = bt_echo(tml);
	if (!ft_strcmp(tml->split_cmd[0], "env") && exit_status == 0)
		exit_status = bt_env(tml);
	return (exit_status);
}

int	tml_exec_child(t_ml *tml, int *fd)
{
	int			exit_status;
	t_string	*env_updated;

	exit_status = 0;
	exit_status = rd_redirection(tml, fd);
	if (!ft_strncmp(tml->split_cmd[0], "./", 2) || tml->split_cmd[0][0] == '/')
		exit_status = tml_check_access(tml);
	if (condition_for_find_exec(tml) && exit_status == 0)
		exit_status = tml_find_exec(tml);
	exit_status = exec_builtins(tml, exit_status);
	if (condition_for_exit(tml) || exit_status != 0)
		exit(exit_status);
	env_updated = tml_construct_env(tml);
	if (execve(tml->split_cmd[0], tml->split_cmd, env_updated) == -1)
	{
		tml_free_sprt_cmd(env_updated);
		tml->running = EXIT_SILENCED;
		exit_status = 1;
	}
	return (exit_status);
}
