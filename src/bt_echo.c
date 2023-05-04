/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:05:28 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 18:03:36 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_echo(t_ml *tml)
{
	int		i;
	t_bool	f;

	i = 0;
	f = FALSE;
	while (tml->split_cmd[++i])
	{
		if (i == 1 && !ft_strcmp(tml->split_cmd[i], "-n"))
			f = TRUE;
		else
		{
			if (tml->split_cmd[i])
			{
				if ((tml->split_cmd[i + 1] == NULL
						|| !ft_isprint(tml->split_cmd[i + 1][0])))
					printf("%s", tml->split_cmd[i]);
				else
					printf("%s ", tml->split_cmd[i]);
			}
		}
	}
	if (!f)
		printf("\n");
	return (0);
}
