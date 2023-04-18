/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_descompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:41:58 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 20:37:14 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_string	get_between_dollar(t_string new_string,
	t_string string, t_string *temp, int *j)
{
	if (new_string)
	{
		(*temp)[++(*j)] = '\0';
		new_string = ft_strcat(new_string, (*temp), TRUE, TRUE);
		(*temp) = malloc(sizeof(char) * ft_strlen(string) + 1);
		(*j) = -1;
	}
	return (new_string);
}

static t_string	check_env_or_var(t_ml *tml, t_string new_string,
	t_string string, int *i)
{
	t_string	value;

	if (!new_string)
		new_string = ft_substr(string, 0, (*i));
	value = get_env(tml->env_vars, string, i);
	if (!ft_strcmp(value, ""))
		value = ft_strrpc(value, get_env(tml->local_vars, string, i), TRUE, TRUE);
	if (!ft_strcmp(value, ""))
		value = ft_strrpc(value, get_var(tml, string, i), TRUE, TRUE);
	new_string = ft_strcat(new_string, value, TRUE, TRUE);
	return (new_string);
}

static t_string	complete_new_string(t_string new_string, t_string *temp, int j)
{
	(*temp)[++j] = '\0';
	if ((*temp)[0] != '\0')
		new_string = ft_strcat(new_string, (*temp), TRUE, FALSE);
	free((*temp));
	return (new_string);
}

t_string	vr_descompress(t_ml *tml, t_string string)
{
	int			i;
	int			j;
	t_string	new_string;
	t_string	temp;

	i = -1;
	j = -1;
	new_string = NULL;
	temp = malloc(sizeof(char) * ft_strlen(string) + 1);
	// printf("\033[32m%s\033[0m\n", tml->split_cmd[i]);
	while (string[++i])
	{
		if (new_string && string[i] != '$')
			temp[++j] = string[i];
		if (string[i] == '$' && string[i + 1] != ' ' && string[i + 1] != '\0')
		{
			new_string = get_between_dollar(new_string, string, &temp, &j);
			new_string = check_env_or_var(tml, new_string, string, &i);
		}
	}
	new_string = complete_new_string(new_string, &temp, j);
	if (new_string)
		string = ft_strrpc(string, new_string, TRUE, TRUE);
	return (string);
}
