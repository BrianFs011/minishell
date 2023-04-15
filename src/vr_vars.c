/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:55:15 by briferre          #+#    #+#             */
/*   Updated: 2023/04/04 11:52:08 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_varlist	vr_get_name_value(t_string envs)
{
	int			i;
	int			cont;
	t_varlist	vars;

	i = -1;
	cont = 0;
	while (envs[++i] && envs[i] != '=')
		cont++;
	vars.name = ft_substr(envs, 0, cont);
	vars.value = ft_substr(envs, cont + 1, ft_strlen(envs));
	return (vars);
}
