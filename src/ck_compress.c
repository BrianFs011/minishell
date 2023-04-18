/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_compress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:12:31 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 20:26:28 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_string	new_lines(char c)
{
	t_string	line;
	t_string	strings;

	line = readline("> ");
	line = ft_strcat(line, "\n", TRUE, FALSE);
	strings = ft_strcpy(line, FALSE);
	while (!ft_cc(line, c))
	{
		free(line);
		line = readline("> ");
		line = ft_strcat(line, "\n", TRUE, FALSE);
		strings = ft_strcat(strings, line, TRUE, FALSE);
	}
	free(line);
	return (strings);
}

static t_varlist	construct_var(t_ml *tml, int i, int temp_i, char c)
{
	t_varlist	cmd_var;

	(void)c;
	cmd_var.name = ft_itoa(temp_i);
	cmd_var.value = ft_substr(tml->cmd, temp_i, i - temp_i + 1);
	return (cmd_var);
}

static void	ck_compress(t_ml *tml, int *i, char c)
{
	int				temp_i;
	t_string		new_cmd;
	t_varlist		cmd_var;

	temp_i = (*i);
	while (tml->cmd[++(*i)] && tml->cmd[(*i)] != c)
		;
	if (tml->cmd[(*i)] != '\0')
	{
		cmd_var = construct_var(tml, (*i), temp_i, c);
		new_cmd = ft_substr(tml->cmd, 0, temp_i);
		new_cmd = ft_strcat(new_cmd, ft_strcat("$", cmd_var.name, FALSE, FALSE),
				TRUE, TRUE);
		vr_insert(&tml->quotes_vars, cmd_var);
		new_cmd = ft_strcat(new_cmd, ft_substr(tml->cmd, (*i) + 1,
					ft_strlen(tml->cmd) - (*i)), TRUE, TRUE);
		tml->cmd = ft_strrpc(tml->cmd, new_cmd, TRUE, TRUE);
		(*i) = temp_i;
	}
	else
	{
		tml->cmd = ft_strcat(tml->cmd, new_lines(c), TRUE, TRUE);
		(*i) = temp_i - 1;
	}
}

int	ck_quotes(t_ml *tml)
{
	int			i;

	i = -1;
	while (tml->cmd[++i])
	{
		if (tml->cmd[i] == '\"')
			ck_compress(tml, &i, '\"');
		else if (tml->cmd[i] == '\'')
			ck_compress(tml, &i, '\'');
	}
	return (0);
}
