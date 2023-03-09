/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:55:15 by briferre          #+#    #+#             */
/*   Updated: 2023/03/04 15:11:29 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	vr_add_variable(t_ml *tml)
{
	int		i;
	int		cont;
	t_vars	vars;

	i = -1;
	cont = 0;
	while (tml->cmd[++i] != '=')
		cont++;
	vars.name = malloc(sizeof(char) * cont + 1);
	ft_memcpy(vars.name, tml->cmd, cont);
	vars.name[cont] = '\0';
	cont = 0;
	while (tml->cmd[++i])
		cont++;
	tml->cmd += i - cont;
	vars.value = malloc(sizeof(char) * cont + 1);
	ft_memcpy(vars.value, tml->cmd, cont);
	vars.value[cont] = '\0';
	tml->cmd -= i - cont;
	vr_insert(&tml->vars, vars);
}
