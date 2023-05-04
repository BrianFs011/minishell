/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:31:44 by briferre          #+#    #+#             */
/*   Updated: 2023/05/03 20:25:25 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	pp_switch(t_ml *tml)
{
	if (tml->i == tml->pp_quant && tml->redirect_in != 1)
	{
		if (fd_dup2(tml->pp_lpipes[tml->i - 1][0], STDIN_FILENO))
			tml_set_pexit_status("dup2", EXIT_FAILURE);
		fd_close(tml->pp_lpipes[tml->i - 1][1]);
	}
	else if (tml->i == tml->pp_quant && tml->redirect_in == 1)
		fd_close(tml->pp_lpipes[tml->i - 1][1]);
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
