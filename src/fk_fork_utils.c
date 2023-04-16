/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/04/16 14:41:13 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fk_call_new_process(pid_t pid, t_ml *tml)
{
	int	fd;
	// int	status;
	t_varlist	var;

	fd = -10;
	if (pid == -1)
		perror("Erro ao criar o processo filho\n");
	else if (pid != 0)
	{
		g_pid = pid;
		var.name = ft_strcpy("pid", FALSE);
		var.value = ft_strcpy(ft_itoa(pid), TRUE);
		vr_insert(&tml->pid_list, var);
		if (fd != -10)
			close(fd);
		if (tml->pp_quant != 0 && !(tml->i == tml->pp_quant))
			close(tml->pp_lpipes[tml->i][1]);
		tml_exec_father(tml);
		tml->exit_status = 0;
		g_pid = G_FATHER;
	}
	else
	{
		g_pid = G_CHILD;
		tml->exit_status = tml_exec_child(tml, &fd);
	}
}

//wait pid

void	ft_wait_execs(t_ml *data)
{
	int	new_exit_code;

	while (data->pid_list)
	{
		waitpid((*(pid_t *)data->pid_list->value), &new_exit_code, 0);
		new_exit_code = WEXITSTATUS(new_exit_code);
		// pp_error(tml, &status);
		data->pid_list = data->pid_list->next;
	}
	tml_exit_status(&data->assigned, new_exit_code, FALSE);
}
