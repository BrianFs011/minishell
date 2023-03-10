/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:55:15 by briferre          #+#    #+#             */
/*   Updated: 2023/03/09 19:05:14 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	vr_add_variable(t_ml *tml)
// {
// 	int		i;
// 	int		cont;
// 	t_vars	vars;

// 	i = -1;
// 	cont = 0;
// 	while (tml->cmd[++i] != '=')
// 		cont++;
// 	vars.name = ft_substr(tml->cmd, 0, cont);
// 	vars.value = ft_substr(tml->cmd, cont + 1, ft_strlen(tml->cmd));
// 	vr_insert(&tml->vars, vars);
// }


void	vr_add_variable(t_vars **start, t_string envs)
{
	int		i;
	int		cont;
	t_vars	vars;

	i = -1;
	cont = 0;
	while (envs[++i] != '=')
		cont++;
	vars.name = ft_substr(envs, 0, cont);
	vars.value = ft_substr(envs, cont + 1, ft_strlen(envs));
	vr_insert(start, vars);
}
