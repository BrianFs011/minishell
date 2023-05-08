/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/05/07 17:49:11 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_sigquit(int signal)
{
	(void)signal;
	printf("Quit\n");
}

static void	fk_save_pid(t_ml *tml, int pid)
{
	t_varlist	var;

	var.name = ft_strcpy("pid", FALSE);
	var.value = ft_strcpy(ft_itoa(pid), TRUE);
	vr_insert(&tml->pid_list, var, TRUE, TRUE);
}

void	fk_call_new_process(t_ml *tml)
{
	int			fd;
	pid_t		pid;

	fd = -10;
	if (pipe(tml->fd_pipe) == -1)
		perror("Pipe fail. Could not pipe files.");
	pid = fork();
	if (pid == -1)
		perror("Erro ao criar o processo filho\n");
	else if (pid != 0)
	{
		g_pid = pid;
		pp_switch(tml, &fd);
		signal(SIGQUIT, handle_sigquit);
		fk_save_pid(tml, pid);
	}
	else
	{
		g_pid = G_CHILD;
		signal(SIGQUIT, SIG_DFL);
		tml->exit_status = tml_exec_child(tml, &fd);
	}
}

void	fk_wait_execs(t_ml *tml)
{
	int			new_exit_code;
	pid_t		pid;
	t_varlist	*temp;

	temp = tml->pid_list;
	new_exit_code = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->name, "pid"))
		{
			pid = ft_atoi(temp->value);
			waitpid(pid, &new_exit_code, 0);
			new_exit_code = WEXITSTATUS(new_exit_code);
		}
		else
			new_exit_code = ft_atoi(temp->value);
		temp = temp->next;
	}
	vr_delete(&tml->pid_list);
	tml->pid_list = NULL;
	tml_exit_status(&tml->local_vars, new_exit_code, FALSE);
	tml->exit_status = new_exit_code;
}
