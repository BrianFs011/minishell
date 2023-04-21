/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:50:23 by briferre          #+#    #+#             */
/*   Updated: 2023/04/19 17:35:18 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_exit(t_ml *tml)
{
	// printf("%p\n", tml->split_cmd[2]);
	if (!ft_strcmp(tml->split_cmd[0], "exit"))
	{
		if (tml->split_cmd[1] == NULL)
			tml->running = FALSE;
		else
			printf("bash: exit: too many arguments\n");
	}
	return (tml->exit_status);
}
