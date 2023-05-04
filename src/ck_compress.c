/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_compress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:12:31 by briferre          #+#    #+#             */
/*   Updated: 2023/05/04 19:00:29 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_varlist	construct_var(t_ml *tml, int i, int temp_i, char c)
{
	t_varlist	cmd_var;

	(void)c;
	cmd_var.name = ft_itoa(temp_i);
	cmd_var.value = ft_substr(tml->cmd, temp_i, i - temp_i + 1);
	return (cmd_var);
}

static int	if_quote_are_not_closed(void)
{
	ft_print_error(NULL, "syntax error quotes were not closed", FALSE);
	return (1);
}

static int	ck_compress(t_ml *tml, int *i, char c)
{
	int				temp_i;
	t_string		new_cmd;
	t_varlist		cmd_var;

	temp_i = (*i);
	new_cmd = NULL;
	while (tml->cmd[++(*i)] && tml->cmd[(*i)] != c)
		;
	if (tml->cmd[(*i)] != '\0')
	{
		cmd_var = construct_var(tml, (*i), temp_i, c);
		new_cmd = ft_substr(tml->cmd, 0, temp_i);
		new_cmd = ft_strcat(new_cmd, ft_strcat("$", cmd_var.name, FALSE, FALSE),
				TRUE, TRUE);
		vr_update_insert(&tml->quotes_vars, cmd_var);
		new_cmd = ft_strcat(new_cmd, ft_substr(tml->cmd, (*i) + 1,
					ft_strlen(tml->cmd) - (*i)), TRUE, TRUE);
		tml->cmd = ft_strrpc(tml->cmd, new_cmd, TRUE, TRUE);
		(*i) = temp_i;
	}
	else
		return (if_quote_are_not_closed());
	return (0);
}

int	ck_quotes(t_ml *tml)
{
	int			i;
	int			exit_status;

	i = -1;
	exit_status = 0;
	while (exit_status == 0 && tml->cmd[++i])
	{
		if (tml->cmd[i] == '\"')
			exit_status = ck_compress(tml, &i, '\"');
		else if (tml->cmd[i] == '\'')
			exit_status = ck_compress(tml, &i, '\'');
	}
	return (exit_status);
}
