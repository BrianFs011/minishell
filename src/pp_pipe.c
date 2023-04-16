/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:31:44 by briferre          #+#    #+#             */
/*   Updated: 2023/04/16 16:31:19 by sde-cama         ###   ########.fr       */
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
		tml->sprt_cmd = ft_split(tml->pp_cmd[tml->i], ' ');
		i = -1;
		while (tml->sprt_cmd[++i])
		{
			tml->sprt_cmd[i] = vr_descompress(tml, tml->sprt_cmd[i]);
			// printf("\001\033[32m\002sprt\001\033[0m\002: |%s|\n", tml->sprt_cmd[i]);
		}
		check_empty_line(tml);
		fk_call_new_process(tml);
		tml_free_sprt_cmd(tml->sprt_cmd);
	}
	ft_wait_execs(tml);// rever localização
	if (tml->pp_quant > 0)
		pp_delete_linked_pipes(tml);
}

void	pp_switch(t_ml *tml)
{
	if (tml->i == tml->pp_quant)
		dup2(tml->pp_lpipes[tml->i - 1][0], STDIN_FILENO);
	else if (tml->i == 0)
		dup2(tml->pp_lpipes[tml->i][1], STDOUT_FILENO);
	else
	{
		if (dup2(tml->pp_lpipes[tml->i - 1][0], STDIN_FILENO) == -1)
			tml_set_pexit_status("dup2", EXIT_FAILURE);
		close(tml->pp_lpipes[tml->i][0]);
		if (dup2(tml->pp_lpipes[tml->i][1], STDOUT_FILENO) == -1)
			tml_set_pexit_status("dup2", EXIT_FAILURE);
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
		free(tml->pp_lpipes[i]);
	free(tml->pp_lpipes);
	tml->pp_lpipes = NULL;
}
