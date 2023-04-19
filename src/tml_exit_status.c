/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:42:41 by briferre          #+#    #+#             */
/*   Updated: 2023/04/18 20:54:32 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_exit_status(t_varlist **start, int value, int init)
{
	t_varlist	var;

	var.name = ft_strcpy("?", FALSE);
	var.value = ft_strcpy(ft_itoa(value), TRUE);
	vr_update_insert(start, var);
	if (!init)
		free(var.name);
}

int	tml_set_exit_status(t_string msg, int exit)
{
	printf("%s", msg);
	return (exit);
}

int	tml_set_pexit_status(char *message, int type)
{
	perror(message);
	return (type);
}
