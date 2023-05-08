/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 11:29:06 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	rd_out(t_ml *tml, int *fd, int *i)
{
	int	oflag;

	if (!strcmp(tml->split_cmd[*i], ">") || !strcmp(tml->split_cmd[*i], ">>"))
	{
		oflag = O_CREAT | O_WRONLY | O_TRUNC;
		if (!strcmp(tml->split_cmd[*i], ">"))
			*fd = open (tml->split_cmd[++(*i)], oflag, 0644);
		oflag = O_WRONLY | O_APPEND | O_CREAT;
		if (!strcmp(tml->split_cmd[*i], ">>"))
			*fd = open (tml->split_cmd[++(*i)], oflag, 0644);
		if (*fd == -1)
			return (tml_set_pexit_status(tml->split_cmd[*i], 1));
		if (fd_dup2(*fd, STDOUT_FILENO))
			return (tml_set_pexit_status("dup2", 1));
		tml->redirect_out = 1;
	}
	return (0);
}

static int	rd_in(t_ml *tml, int *fd, int *i)
{
	if (!strcmp(tml->split_cmd[*i], "<"))
	{
		*fd = open(tml->split_cmd[++(*i)], O_RDONLY, 0644);
		if (*fd == -1)
		{
			if (tml->split_cmd[(*i)])
				return (tml_set_pexit_status(tml->split_cmd[(*i)], 1));
			else
				return (tml_set_pexit_status("missing", 1));
		}
		if (fd_dup2(*fd, STDIN_FILENO))
			return (tml_set_pexit_status("dup2", 1));
		tml->redirect_in = 1;
	}
	return (0);
}

int	rd_redirection(t_ml *tml, int *fd)
{
	int			i;
	int			exit_status;

	exit_status = 0;
	i = -1;
	while (tml->split_cmd[++i])
	{
		exit_status = rd_in(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
		exit_status = rd_out(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
	}
	if (tml->here_doc)
		set_here_doc(tml->here_doc);
	if ((exit_status == 0 && (*fd) != -10) || tml->here_doc)
		remove_redirection(tml);
	return (exit_status);
}
