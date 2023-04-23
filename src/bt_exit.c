/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:50:23 by briferre          #+#    #+#             */
/*   Updated: 2023/04/23 14:58:01 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	exit_error(t_string cmd, t_string msg, int exit_status)
{
	ft_print_error(cmd, msg, FALSE);
	return (exit_status);
}

int	bt_exit(t_ml *tml)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp(tml->split_cmd[0], "exit"))
		tml->running = FALSE;
	if (!tml->split_cmd[1])
		return (exit_status);
	else if (tml->split_cmd[1] && !tml->split_cmd[2])
	{
		if (ft_foreach(tml->split_cmd[1], ft_isdigit_plus) == -1)
		{
			if (ck_isllongint(tml->split_cmd[1]))
				exit_status = ft_atoi_llint(tml->split_cmd[1]) % 256;
			else
				exit_status = exit_error(tml->split_cmd[0],
						": numeric argument required", 2);
		}
		else
			exit_status = exit_error(tml->split_cmd[0],
					": numeric argument required", 2);
	}
	else
		exit_status = exit_error(tml->split_cmd[0], ": too many arguments", 1);
	return (exit_status);
}
