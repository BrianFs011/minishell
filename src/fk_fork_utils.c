/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/03/09 07:09:46 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fk_call_new_process(pid_t pid, t_ml *tml)
{
	int	fd;

	fd = -10;
	if (pid == -1)
		perror("Erro ao criar o processo filho\n");
	else if (pid != 0)
	{
		wait(&pid);
		close(fd);
		if (tml->pp_quant != 0 && !(tml->i == tml->pp_quant))
			close(tml->pp_lpipes[tml->i][1]);
	}
	else
		tml_exec(tml, &fd);
}
