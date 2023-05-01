/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:42:41 by briferre          #+#    #+#             */
/*   Updated: 2023/05/01 11:30:47 by sde-cama         ###   ########.fr       */
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
	t_string	new_msg;

	new_msg = ft_strcat("minishell: ", message, FALSE, FALSE);
	perror(new_msg);
	return (type);
}
