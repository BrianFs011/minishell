/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:05:28 by briferre          #+#    #+#             */
/*   Updated: 2023/04/19 18:35:05 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_echo(t_string *splt)
{
	int		i;
	t_bool	f;

	i = 0;
	f = FALSE;
	// ft_putstr_fd();
	while (splt[++i])
	{
		if (i == 1 && !ft_strcmp(splt[i], "-n"))
			f = TRUE;
		else
		{
			if (!ft_strcmp(splt[i], ">>") || !ft_strcmp(splt[i], ">")
				|| !ft_strcmp(splt[i], "<") || !ft_strcmp(splt[i], "<<"))
				break ;
			if (splt[i] && splt[i + 1] == NULL)
				printf("%s", splt[i]);
			else
				printf("%s ", splt[i]);
			// printf("\033[37m%s\033[0m ", splt[i]);
		}
	}
	if (!f)
		printf("\n");
	return (0);
}
