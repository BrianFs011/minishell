/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/04/18 20:45:17 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct s_teste
{

}t_teste;

void	fk_call_new_process(t_ml *tml)
{
	int			fd;
	pid_t		*pid;
	t_list		*var;

	fd = -10;
	pid = malloc(sizeof(pid_t));
	*pid = fork();
	if (*pid == -1)
		perror("Erro ao criar o processo filho\n");
	else if (*pid != 0)
	{
		g_pid = *pid;
		var = ft_lstnew(pid);
		ft_lstadd_back(&tml->pid_list, var);
		if (fd != -10)
			close(fd);
		if (tml->pp_quant != 0 && !(tml->i == tml->pp_quant))
			close(tml->pp_lpipes[tml->i][1]);
		// tml_exec_father(tml);
		tml->exit_status = 0;
		g_pid = G_FATHER;
	}
	else
	{
		g_pid = G_CHILD;
		tml->exit_status = tml_exec_child(tml, &fd);
	}
}

void	fk_wait_execs(t_ml *tml)
{
	int			new_exit_code;
	pid_t		*pid;
	t_list	*temp;

	temp = tml->pid_list;
	while (temp)
	{
		pid = temp->content;
		waitpid(*pid, &new_exit_code, 0);
		new_exit_code = WEXITSTATUS(new_exit_code);
		// pp_error(tml, &status);
		temp = temp->next;
	}
	ft_lstclear(&tml->pid_list, free);
	tml->pid_list = NULL;
	tml_exit_status(&tml->local_vars, new_exit_code, FALSE);
}
