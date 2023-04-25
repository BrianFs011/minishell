/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:09:40 by briferre          #+#    #+#             */
/*   Updated: 2023/04/25 12:50:11 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	unexpected_token(char token)
{
	if (
		token == '<'
		|| token == '>'
		|| token == '|'
		|| token == '#'
		|| token == '&'
		|| token == ')'
		|| token == '('
	)
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			token);
		return (1);
	}
	return (0);
}

int	ck_redictions(t_ml *tml)
{
	t_string	new_cmd;
	int			i;

	i = -1;
	new_cmd = NULL;
	while (tml->cmd[++i])
	{
		if ((tml->cmd[i] == '<' || tml->cmd[i] == '>') && tml->cmd[i - 1] != ' ' && !(tml->cmd[i - 1] == '<' || tml->cmd[i - 1] == '>'))
		{
			new_cmd = ft_strcatc(new_cmd, ' ', TRUE);
			if (unexpected_token(tml->cmd[++i]))
			{
				tml_exit_status(&tml->local_vars, 2, FALSE);
				free(new_cmd);
				return (2);
			}
		}
		new_cmd = ft_strcatc(new_cmd, tml->cmd[i], TRUE);
		if ((tml->cmd[i] == '<' || tml->cmd[i] == '>') && tml->cmd[i + 1] != ' ' && !(tml->cmd[i + 1] == '<' || tml->cmd[i + 1] == '>'))
		{
			new_cmd = ft_strcatc(new_cmd, ' ', TRUE);
			if (unexpected_token(tml->cmd[++i]))
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

// int	ck_redictions(t_ml *tml)
// {
	// int			i;
	// int			exit_status;
	// t_string	new;
	// t_string	after;

	// printf("\033[33mck_redirect\033[0m: %s\n", tml->cmd);
	// i = -1;
	// new = NULL;
	// exit_status = 0;
	// while (tml->cmd[++i])
	// {
	// 	if (tml->cmd[i] == '<' || tml->cmd[i] == '>')
	// 	{
	// 		new = get_before(tml->cmd, &i);
	// 		new = ft_strcat(new, get_operator(tml->cmd, &i), TRUE, TRUE);
	// 		after = get_after(tml->cmd, &i);
	// 		// printf("%p\n", after);
	// 		if (!after)
	// 		{
	// 			exit_status = 2;
	// 			after = "syntax error near unexpected token `newline'\n";
	// 			tml_exit_status(&tml->local_vars, exit_status, FALSE);
	// 			free(new);
	// 			return (tml_set_exit_status(after, exit_status));
	// 		}
	// 		new = ft_strcat(new, after, TRUE, TRUE);
	// 	}
	// }
	// printf("\033[35mnew\033[0m: %s|\n", new);
	// if (new)
	// 	tml->cmd = ft_strrpc(tml->cmd, new, TRUE, TRUE);
	// printf("\033[33mck_redirect\033[0m: %s\n", tml->cmd);
	// tml->cmd = ft_strrpc(tml->cmd)
// 	return (ft_new(tml));
// }


// t_string	get_before(t_string string, int *i)
// {
// 	t_string	before;

// 	before = ft_substr(string, 0, (*i));
// 	// printf("\033[32mget_before\033[0m: %s | %c\n", before, string[*i]);
// 	if (string[(*i) - 1] != ' ')
// 		before = ft_strcat(before, " ", TRUE, FALSE);
// 	else if (string[(*i)] == ' ')
// 		(*i)++;
// 	// printf("\033[34mget_before\033[0m: %s | %c\n", before, string[*i]);
// 	return (before);
// }

// t_string	get_operator(t_string string, int *i)
// {
// 	t_string	before;

// 	if (string[*i] == '>')
// 	{
// 		before = ft_strcpy(">", FALSE);
// 		if (string[(*i) + 1] == '>')
// 		{
// 			before = ft_strcat(before, ">", TRUE, FALSE);
// 			(*i)++;
// 		}
// 	}
// 	else if (string[*i] == '<')
// 	{
// 		before = ft_strcpy("<", FALSE);
// 		if (string[(*i) + 1] == '<')
// 		{
// 			before = ft_strcat(before, "<", TRUE, FALSE);
// 			(*i)++;
// 		}
// 	}
// 	if (string[++(*i)] != ' ')
// 		before = ft_strcat(before, " ", TRUE, FALSE);
// 	return (before);
// }

// t_string	get_after(t_string string, int *i)
// {
// 	t_string	after;
// 	int			size_string;

// 	after = NULL;
// 	size_string = ft_strlen(string);
// 	if (size_string > (*i))
// 		after = ft_substr(string, (*i), size_string - (*i));
// 	// printf("\033[36mget_before\033[0m: |%s| %d %d\n", after, size_string, (*i));
// 	if (after && unexpected_token(after))
// 	{
// 		free(after);
// 		after = NULL;
// 	}
// 	return (after);
// }

// int	ft_istrchr(t_string string, char c)
// {
// 	int	i;

// 	i = -1;
// 	while (string[++i])
// 		if (string[i] == c)
// 			return (i);
// 	return (-1);
// }

// int	redirect_input(t_ml *tml)
// {
// 	t_string	before_c;
// 	t_string	after_c;
// 	int			p;

// 	p = ft_istrchr(tml->cmd, '<');
// 	before_c = ft_substr(tml->cmd, 0, p);
// 	after_c = ft_substr(tml->cmd, p, ft_strlen(tml->cmd) - p);
// 	if (after_c)
// 	{
// 		if (unexpected_token(after_c))
// 			return (1);
// 		if (!ft_strncmp(after_c, "<<", 2))
// 			return (0);
// 		if (before_c[p - 1] != ' ')
// 			before_c = ft_strcat(before_c, " ", TRUE, FALSE);
// 		if (after_c[1] != ' ')
// 		{
// 			before_c = ft_strcat(before_c, "< ", TRUE, FALSE);
// 			before_c = ft_strcat(before_c, ft_substr(after_c, 1,
// 						ft_strlen(after_c) - 2), TRUE, FALSE);
// 		}
// 		else
// 			before_c = ft_strcat(before_c, after_c, TRUE, TRUE);
// 	}
// 	tml->cmd = ft_strrpc(tml->cmd, before_c, TRUE, TRUE);
// 	return (0);
// }
	// printf("\033[33mck_redirect\033[0m: %s\n", tml->cmd);
	// // if (ft_cc(tml->cmd, '<'))
	// // 	redirect_input(tml);
	// printf("\033[33mck_redirect\033[0m: %s\n", tml->cmd);