/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:31:44 by briferre          #+#    #+#             */
/*   Updated: 2023/04/30 14:25:47 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	pp_call_pipe(t_ml *tml)
{
	int	i;

	if (tml->pp_quant > 0)
		pp_linked_pipes(tml);
	tml->i = -1;
	while (++tml->i <= tml->pp_quant && tml->running == RUNNIG)
	{
		tml->split_cmd = ft_split(tml->pp_cmd[tml->i], ' ');
		i = -1;
		while (tml->split_cmd[++i])
		{
			tml->split_cmd[i] = vr_descompress(tml, tml->split_cmd[i]);
			// printf("\001\033[32m\002sprt\001\033[0m\002: |%s|\n", tml->split_cmd[i]);
		}
		check_empty_line(tml);
		if (tml_exec_father(tml) == -1)
			fk_call_new_process(tml);
		tml_free_sprt_cmd(tml->split_cmd);
	}
	if (tml->pp_quant > 0)
		pp_delete_linked_pipes(tml);
	fk_wait_execs(tml);
}

void	pp_switch(t_ml *tml)
{
	if (tml->i == tml->pp_quant)
	{
		fd_close(tml->pp_lpipes[tml->i - 1][1]);
		if (fd_dup2(tml->pp_lpipes[tml->i - 1][0], STDIN_FILENO))
			tml_set_pexit_status("dup2", EXIT_FAILURE);
	}
	else if (tml->i == 0)
	{
		fd_close(tml->pp_lpipes[tml->i][0]);
		if (fd_dup2(tml->pp_lpipes[tml->i][1], STDOUT_FILENO))
			tml_set_pexit_status("dup2", EXIT_FAILURE);
	}
	else
	{
		if (fd_dup2(tml->pp_lpipes[tml->i - 1][0], STDIN_FILENO))
			tml_set_pexit_status("dup2", EXIT_FAILURE);
		fd_close(tml->pp_lpipes[tml->i - 1][1]);
		if (fd_dup2(tml->pp_lpipes[tml->i][1], STDOUT_FILENO))
			tml_set_pexit_status("dup2", EXIT_FAILURE);
		fd_close(tml->pp_lpipes[tml->i][0]);
	}
}

void	pp_linked_pipes(t_ml *tml)
{
	int	i;

	if (tml->pp_quant < 1)
		return ;
	tml->pp_lpipes = malloc(sizeof(int *) * tml->pp_quant);
	i = -1;
	while (++i < tml->pp_quant)
	{
		tml->pp_lpipes[i] = malloc(sizeof(int) * 2);
		pipe(tml->pp_lpipes[i]);
	}
}

void	pp_delete_linked_pipes(t_ml *tml)
{
	int	i;

	i = -1;
	while (++i < tml->pp_quant)
	{
		fd_close(tml->pp_lpipes[i][1]);
		fd_close(tml->pp_lpipes[i][0]);
		free(tml->pp_lpipes[i]);
	}
	free(tml->pp_lpipes);
	tml->pp_lpipes = NULL;
}
