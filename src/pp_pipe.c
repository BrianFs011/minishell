/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:15:22 by sde-cama          #+#    #+#             */
/*   Updated: 2023/05/07 13:15:58 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	pp_switch(t_ml *tml, int *fd)
{
	if (g_pid == G_CHILD)
	{
		close(tml->fd_pipe[0]);
		if (tml->pp_quant != 0
			&& tml->i != tml->pp_quant && tml->redirect_out != 1)
			fd_dup2(tml->fd_pipe[1], STDOUT_FILENO);
		else if (tml->pp_quant != 0 && tml->i == tml->pp_quant)
			fd_close(tml->fd_pipe[1]);
	}
	else
	{
		if (*fd && *fd != -10)
			fd_close(*fd);
		fd_close(tml->fd_pipe[1]);
		if (tml->pp_quant != 0 && tml->redirect_in != 1)
			fd_dup2(tml->fd_pipe[0], STDIN_FILENO);
		else
			fd_close(tml->fd_pipe[0]);
	}
}
