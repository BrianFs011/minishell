/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:53 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 16:06:52 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_interrupt(int signal)
{
	(void)signal;
	if (g_pid == G_FATHER)
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
