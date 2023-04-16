/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:50:23 by briferre          #+#    #+#             */
/*   Updated: 2023/04/16 10:37:48 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_exit(t_ml *tml)
{
	// printf("%p\n", tml->sprt_cmd[2]);
	if (!ft_strcmp(tml->sprt_cmd[0], "exit"))
	{
		if (tml->sprt_cmd[1] == NULL)
			tml->running = FALSE;
		else
			printf("bash: exit: too many arguments\n");
	}
	return (0);
}
