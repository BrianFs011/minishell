/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:53 by briferre          #+#    #+#             */
/*   Updated: 2023/04/30 16:16:39 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	force_free(t_ml *tml)
{
	if (tml->pp_quant > 0)
		pp_delete_linked_pipes(tml);
	if (tml->cmd)
		ft_free(tml->cmd);
	tml_free_sprt_cmd(tml->split_cmd);
	tml_free_sprt_cmd(tml->pp_cmd);
	vr_delete(&tml->quotes_vars);
	ft_free(tml->pwd);
	ft_free(tml->prompt);
	tml_free_uhp(tml);
	vr_delete(&tml->pid_list);
	vr_delete(&tml->local_vars);
	vr_delete(&tml->env_vars);
	rl_clear_history();
}

static void	handle_interrupt(int signal)
{
	t_ml	*tml;

	(void)signal;
	tml = NULL;
	if (g_pid == G_CHILD)
	{
		tml = save_point(tml, FALSE);
		force_free(tml);
		printf("\n");
		exit(130);
	}
	else if (g_pid == G_FATHER)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sa_hooks(void)
{
	t_sigaction	action;

	signal_hook(&action, handle_interrupt, SIGINT);
	signal_hook(&action, SIG_IGN, SIGQUIT);
}
