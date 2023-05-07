/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_scroll_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:26:30 by briferre          #+#    #+#             */
/*   Updated: 2023/05/06 23:12:58 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	broke_in_spaces(t_ml *tml)
{
	int	i;

	tml->split_cmd = ft_split(tml->pp_cmd[tml->i], ' ');
	i = -1;
	while (tml->split_cmd[++i])
		tml->split_cmd[i] = vr_descompress(tml, tml->split_cmd[i]);
	check_empty_line(tml);
}

static void	have_command(t_ml *tml)
{
	broke_in_spaces(tml);
	if (tml->split_cmd[0])
	{
		if (tml_exec_father(tml) == -1)
			fk_call_new_process(tml);
	}
	tml_free_sprt_cmd(tml->split_cmd);
}

static int	do_not_have_command(t_ml *tml)
{
	int	exit_code;

	exit_code = 2;
	ft_print_error(NULL, "Syntax error", FALSE);
	tml_exit_status(&tml->local_vars, exit_code, FALSE);
	return (exit_code);
}

void	tml_scroll_pipe_list(t_ml *tml)
{
	int	exit_code;

	exit_code = 0;
	tml->i = -1;
	while (++tml->i <= tml->pp_quant && tml->running == RUNNIG
		&& exit_code == 0)
	{
		if (tml->pp_cmd[tml->i])
			have_command(tml);
		else
			exit_code = do_not_have_command(tml);
	}
	if (exit_code == 0)
		fk_wait_execs(tml);
}
