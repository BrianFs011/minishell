/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/04/07 08:57:39 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fk_call_new_process(pid_t pid, t_ml *tml)
{
	int	fd;
	int	status;

	fd = -10;
	if (pid == -1)
		perror("Erro ao criar o processo filho\n");
	else if (pid != 0)
	{
		g_pid = pid;
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
		// pp_error(tml, &status);
		if (fd != -10)
			close(fd);
		if (tml->pp_quant != 0 && !(tml->i == tml->pp_quant))
			close(tml->pp_lpipes[tml->i][1]);
		if (status == 0)
			status = tml_exec_father(tml);
		tml_exit_status(&tml->assigned, status, FALSE);
		tml->exit_status = 0;
		g_pid = G_FATHER;
	}
	else
	{
		g_pid = G_CHILD;
		tml->exit_status = tml_exec_child(tml, &fd);
	}
}
