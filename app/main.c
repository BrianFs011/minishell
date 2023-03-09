/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:57:24 by briferre          #+#    #+#             */
/*   Updated: 2023/03/09 15:49:27 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_call(t_ml *tml)
{
	ck_check(tml);
	tml->sprt_cmd = ft_split(tml->cmd, ' ');
	tml->pp_quant = ft_cc(tml->cmd, '|');
	tml->pp_cmd = ft_split(tml->cmd, '|');
	if (!ft_strcmp(tml->sprt_cmd[0], "test"))
	{
		// vr_print(tml->vars);
		// rl_on_new_line();
		rl_replace_line("", EOF);
		rl_redisplay();
	}
	else if (ft_cc(tml->sprt_cmd[0], '='))
		vr_add_variable(tml);
	else if (!ft_strcmp(tml->sprt_cmd[0], "exit"))
		ft_exit(tml);
	else if (!ft_strcmp(tml->sprt_cmd[0], "cd"))
		tml_cd(tml);
	else if (tml->pp_quant > 0)
		pp_call_pipe(tml);
	else
		fk_call_new_process(fork(), tml);
	tml_free_sprt_cmd(tml->sprt_cmd);
	tml_free_sprt_cmd(tml->pp_cmd);
}

void	tml_loop(t_ml *tml)
{
	tml_create_uhp_line(tml);
	tml->cmd = readline(tml->info);
	if (tml->cmd)
	{
		add_history(tml->cmd);
		if (tml->cmd[0])
			tml_call(tml);
	}
	else
		tml->running = FALSE;
	ft_free(tml->path);
	ft_free(tml->info);
	ft_free(tml->cmd);
}

pid_t	g_pid;

int	main(int argc, t_string *argv, t_string *env)
{
	t_ml			tml;

	(void)argc;
	(void)argv;

	g_pid = 0;
	tml.env = env;
	tml.running = RUNNIG;
	sa_hooks(&tml.sa);
	tml_get_uhp(&tml);
	while (tml.running == RUNNIG)
		tml_loop(&tml);
	if (tml.running == EXIT)
	{
		tml_free_uhp(&tml);
		vr_delete(&tml.vars);
		rl_clear_history();
		printf("Saindo!\n");
	}
	return (0);
}
