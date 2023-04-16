/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/04/16 17:14:03 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fk_call_new_process(t_ml *tml)
{
	int	fd;
	pid_t	pid;
	t_varlist	var;

	fd = -10;
	pid = fork();
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

void	ft_wait_execs(t_ml *tml)
{
	int			new_exit_code;
	t_varlist	*temp;
	pid_t		pid;

	temp = tml->pid_list;
	while (temp)
	{
		pid = ft_atoi(temp->value);
		waitpid(pid, &new_exit_code, 0);
		new_exit_code = WEXITSTATUS(new_exit_code);
		// pp_error(tml, &status);
		temp = temp->next;
	}
	vr_delete(&tml->pid_list);
	tml->pid_list = NULL;
	tml_exit_status(&tml->assigned, new_exit_code, FALSE);
}
