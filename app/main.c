/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:57:24 by briferre          #+#    #+#             */
/*   Updated: 2023/04/19 17:50:48 by briferre         ###   ########.fr       */
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
		pp_call_pipe(tml);
		tml_free_sprt_cmd(tml->pp_cmd);
	}
	// if (tml->env)
	// 	tml_free_sprt_cmd(tml->env);
}

void	tml_loop(t_ml *tml)
{
	tml_create_uhp_line(tml);
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

// int	main(void)
int	main(int argc, t_string *argv, t_string *env)
{
	t_ml			tml;

	tml_init(argc, argv, env, &tml);
	sa_hooks();
	while (tml.running == RUNNIG)
	{
		tml_loop(&tml);
	}
	tml_free_uhp(&tml);
	// tml_free_sprt_cmd(tml.paths);
	vr_delete(&tml.pid_list);
	vr_delete(&tml.local_vars);
	vr_delete(&tml.env_vars);
	rl_clear_history();
	if (tml.running == EXIT)
		printf("%d\n", tml.exit_status);
	return (tml.exit_status);
}
