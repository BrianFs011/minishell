/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_call01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:50:23 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 07:32:34 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_exit(t_ml *tml)
{
	if (!ft_strcmp(tml->sprt_cmd[0], "exit"))
	{
		if (tml->sprt_cmd[2] == NULL)
			tml->running = FALSE;
		else
			printf("bash: exit: too many arguments\n");
	}
	return (0);
}


