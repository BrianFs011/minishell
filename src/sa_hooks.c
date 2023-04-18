/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:53 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 21:13:50 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_interrupt(int signal)
{
	t_ml	t;

	// printf("%d\n", g_pid);
	(void)signal;
	if (g_pid == G_CHILD)
	{
		(void)t;

		// rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
		printf("\n");
		free_tml(&t, 0, 1);
		exit(130);
	}
	else if (g_pid == G_FATHER)
	{
		// printf("pai\n");
		wait (&g_pid);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sa_hooks()
{
	t_sigaction	action;

	signal_hook(&action, handle_interrupt, SIGINT);
	signal_hook(&action, SIG_IGN, SIGQUIT);
}
