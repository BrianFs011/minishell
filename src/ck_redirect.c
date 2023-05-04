/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:09:40 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 19:08:52 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	unexpected_token(char *token, int i)
{
	while (token[++i])
	{
		if (ft_isalnum(token[i]) || token[i] == '.' || token[i] == '$')
			return (0);
		if (
			token[i] == '<'
			|| token[i] == '>'
			|| token[i] == '|'
			|| token[i] == '#'
			|| token[i] == '&'
			|| token[i] == ')'
			|| token[i] == '('
		)
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				token[i]);
			return (1);
		}
	}
	return (0);
}

static int	before_condition(t_ml *tml, int i)
{
	return (
		(tml->cmd[i] == '<' || tml->cmd[i] == '>')
		&& tml->cmd[i - 1] != ' '
		&& !(tml->cmd[i - 1] == '<' || tml->cmd[i - 1] == '>')
	);
}

static int	after_condition(t_ml *tml, int i)
{
	return (
		(tml->cmd[i] == '<' || tml->cmd[i] == '>')
		&& tml->cmd[i + 1] != ' '
		&& !(tml->cmd[i + 1] == '<' || tml->cmd[i + 1] == '>')
	);
}

int	ck_redictions(t_ml *tml)
{
	t_string	new_cmd;
	int			i;

	i = -1;
	new_cmd = NULL;
	while (tml->cmd[++i])
	{
		if (before_condition(tml, i))
			new_cmd = ft_strcatc(new_cmd, ' ', TRUE);
		new_cmd = ft_strcatc(new_cmd, tml->cmd[i], TRUE);
		if (after_condition(tml, i))
		{
			new_cmd = ft_strcatc(new_cmd, ' ', TRUE);
			if (unexpected_token(tml->cmd, i))
			{
				tml_exit_status(&tml->local_vars, 2, FALSE);
				free(new_cmd);
				return (2);
			}
		}
	}
	tml->cmd = ft_strrpc(tml->cmd, new_cmd, TRUE, TRUE);
	return (0);
}
