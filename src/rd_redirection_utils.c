/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/05/04 07:50:22 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ml	*save_point(t_ml *tml, t_bool save)
{
	static t_ml	*tml_save;

	if (save)
		tml_save = tml;
	return (tml_save);
}

int	count_split(t_string *split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

static void	temp_r(t_ml *tml, t_string *split, int *i, int *j)
{
	while (tml->split_cmd[++(*i)])
	{
		if (!ft_strcmp(tml->split_cmd[(*i)], ">>")
			|| !ft_strcmp(tml->split_cmd[(*i)], ">")
			|| !ft_strcmp(tml->split_cmd[(*i)], "<")
			|| !ft_strcmp(tml->split_cmd[(*i)], "<<"))
		{
			if (tml->split_cmd[(*i) + 1])
				(*i)++;
		}
		else
			split[++(*j)] = ft_strcpy(tml->split_cmd[(*i)], FALSE);
	}
	if (++(*j) <= (*i))
		split[(*j)] = NULL;
}

void	remove_redirection(t_ml *tml)
{
	int			i;
	int			j;
	int			split_size;
	t_string	*split;

	split_size = count_split(tml->split_cmd);
	split = malloc(sizeof(t_string) * split_size + sizeof(t_string));
	i = -1;
	j = -1;
	temp_r(tml, split, &i, &j);
	tml_free_sprt_cmd(tml->split_cmd);
	tml->split_cmd = malloc(sizeof(t_string) * j + sizeof(t_string));
	i = -1;
	while (split[++i])
		tml->split_cmd[i] = ft_strcpy(split[i], FALSE);
	tml->split_cmd[i] = NULL;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	set_here_doc(t_string here_doc)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		tml_set_pexit_status("pipe", EXIT_FAILURE);
	ft_putstr_fd(here_doc, fd_pipe[1]);
	close(fd_pipe[1]);
	if (fd_dup2(fd_pipe[0], STDIN_FILENO))
		tml_set_pexit_status("dup2", EXIT_FAILURE);
	close(fd_pipe[0]);
	free(here_doc);
}
