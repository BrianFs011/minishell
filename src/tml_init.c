/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:53:50 by briferre          #+#    #+#             */
/*   Updated: 2023/05/03 13:24:23 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_get_uhp(t_ml *tml)
{
	tml->user = vr_get_value(tml->env_vars, "USER", TRUE);
	tml->host = fl_get_text("/etc/hostname");
	tml->cmd = NULL;
	tml->pp_cmd = NULL;
}

void	tml_init(int argc, t_string *argv, t_string *env, t_ml *tml)
{
	int	i;

	(void)argc;
	(void)argv;
	tml->exit_status = 0;
	i = -1;
	tml->redirect_in = 0;
	tml->redirect_out = 0;
	tml->env_vars = NULL;
	tml->local_vars = NULL;
	tml->pid_list = NULL;
	while (env[++i])
		vr_update_insert(&tml->env_vars, vr_get_name_value(env[i]));
	tml_exit_status(&tml->local_vars, 0, TRUE);
	tml->running = RUNNIG;
	tml->quotes_vars = NULL;
	tml_get_uhp(tml);
}
