/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:42:41 by briferre          #+#    #+#             */
/*   Updated: 2023/04/05 10:34:12 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_exit_status(t_varlist **start, int value, int init)
{
	t_varlist	var;

	var.name = ft_strcpy("?", FALSE);
	var.value = ft_strcpy(ft_itoa(value), TRUE);
	vr_insert(start, var);
	if (!init)
		free(var.name);
}
