/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_descompress_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:45:34 by briferre          #+#    #+#             */
/*   Updated: 2023/04/20 09:08:38 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_empty_line(t_ml *tml)
{
	t_string	aux;
	int			i;

	i = -1;
	while (tml->split_cmd[++i])
	{
		if (!ft_strcmp(tml->split_cmd[i], "") && tml->split_cmd[i + 1])
		{
			aux = tml->split_cmd[i];
			tml->split_cmd[i] = tml->split_cmd[i + 1];
			tml->split_cmd[i + 1] = aux;
		}
	}
}

t_string	get_env(t_varlist *start, t_string string, int *i)
{
	int			j;
	t_string	name;
	t_string	value;

	j = (*i);
	while (string[++(*i)] && string[*i] != ' '
		&& string[*i] != '$' && string[*i] != '\''
		&& string[*i] != '/')
		;
	name = ft_substr(string, j + 1, (*i) - j - 1);
	value = vr_get_value(start, name, TRUE);
	free(name);
	if (!ft_strcmp(value, ""))
	{
		(*i) = j;
		return (value);
	}
	(*i)--;
	return (value);
}

t_string	get_var(t_ml *tml, t_string string, int *i)
{
	int			j;
	t_string	value;
	t_string	name;

	j = (*i);
	while (string[++(*i)] && string[*i] != ' ' && string[*i] != '$'
		&& string[*i] != '\'' && string[*i] != '/' && ft_isdigit(string[*i]))
		;
	name = ft_substr(string, j + 1, (*i) - j - 1);
	value = vr_get_value(tml->quotes_vars, name, TRUE);
	free(name);
	(*i)--;
	if (!ft_strcmp(value, ""))
		return (value);
	if (value[0] == '\"')
	{
		value = ft_strrpc(value, ft_substr(value, 1,
					ft_strlen(value) - 2), TRUE, TRUE);
		value = vr_descompress(tml, value);
	}
	else
		value = ft_strrpc(value, ft_substr(value, 1,
					ft_strlen(value) - 2), TRUE, TRUE);
	return (value);
}

t_string	get_exit_status_var(t_varlist *start, t_string string, int *i)
{
	t_string	value;
	int			j;

	j = (*i);
	if (string[++j] && string[j] == '?')
	{
		value = vr_get_value(start, "?", TRUE);
		(*i) = j;
	}
	else
		value = ft_strcpy("", FALSE);
	return (value);
}
