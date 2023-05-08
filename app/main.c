/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:57:24 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 15:48:28 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

pid_t	g_pid;

void	tml_call(t_ml *tml)
{
	if (ck_check(tml) == 0)
	{
		tml->pp_quant = ft_cc(tml->cmd, '|');
		tml->pp_cmd = ft_split(tml->cmd, '|');
		tml_scroll_pipe_list(tml);
		tml_free_sprt_cmd(tml->pp_cmd);
	}
}

void	tml_loop(t_ml *tml)
{
	if (tml->cmd)
	{
		tml->cmd = NULL;
		if (fd_dup2(tml->stdin, STDIN_FILENO)
			|| fd_dup2(tml->stdout, STDOUT_FILENO))
			tml_set_pexit_status("dup2", EXIT_FAILURE);
		ft_dup_stdin_out(tml);
	}
	tml_create_prompt(tml);
	tml->cmd = readline(tml->prompt);
	if (tml->cmd)
	{
		add_history(tml->cmd);
		if (tml->cmd[0])
			tml_call(tml);
	}
	else
		tml->running = FALSE;
	vr_delete(&tml->quotes_vars);
	ft_free(tml->pwd);
	ft_free(tml->prompt);
	ft_free(tml->cmd);
}

int	main(int argc, t_string *argv, t_string *env)
{
	t_ml			tml;

	tml_init(argc, argv, env, &tml);
	while (tml.running == RUNNIG)
	{
		g_pid = G_FATHER;
		sa_hooks();
		tml_loop(&tml);
	}
	tml_free_uhp(&tml);
	vr_delete(&tml.pid_list);
	vr_delete(&tml.local_vars);
	vr_delete(&tml.env_vars);
	rl_clear_history();
	return (tml.exit_status);
}
