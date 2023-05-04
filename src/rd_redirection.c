/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/05/04 08:00:51 by briferre         ###   ########.fr       */
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

static t_string	rd_in_delimiter(t_ml *tml, t_string hd_eof)
{
	t_string	temp;
	t_string	temp2;

	temp2 = NULL;
	temp = ft_strcpy(" ", FALSE);
	save_point(tml, TRUE);
	while (ft_strcmp(temp, hd_eof))
	{
		free(temp);
		temp = readline("> ");
		if (ft_strcmp(temp, hd_eof))
		{
			temp = vr_descompress(tml, temp);
			if (temp2)
				temp2 = ft_strcat(temp2, temp, TRUE, FALSE);
			else
				temp2 = ft_strcpy(temp, FALSE);
			temp2 = ft_strcat(temp2, "\n", TRUE, FALSE);
		}
	}
	return (temp2);
}

static int	rd_in(t_ml *tml, int *fd, int *i)
{
	if (!strcmp(tml->split_cmd[*i], "<"))
	{
		*fd = open(tml->split_cmd[++(*i)], O_RDONLY, 0644);
		if (*fd == -1)
			return (tml_set_pexit_status("missing", 1));
		if (fd_dup2(*fd, STDIN_FILENO))
			return (tml_set_pexit_status("dup2", 1));
		tml->redirect_in = 1;
	}
	return (0);
}

static void	rd_in_hd(t_ml *tml, int i, int *fd, t_string *here_doc)
{
	if (!strcmp(tml->split_cmd[i], "<<"))
	{
		if (*here_doc == NULL)
			*here_doc = rd_in_delimiter(tml, tml->split_cmd[i + 1]);
		else
			*here_doc = ft_strrpc(*here_doc,
					rd_in_delimiter(tml, tml->split_cmd[i + 1]), TRUE, TRUE);
		*fd = -2;
		tml->redirect_in = 1;
	}
}

int	rd_redirection(t_ml *tml, int *fd)
{
	int			i;
	int			exit_status;
	t_string	here_doc;

	exit_status = 0;
	i = -1;
	here_doc = NULL;
	while (tml->split_cmd[++i])
	{
		exit_status = rd_in(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
		rd_in_hd(tml, i, fd, &here_doc);
		exit_status = rd_out(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
	}
	if (here_doc)
		set_here_doc(here_doc);
	if ((exit_status == 0 && (*fd) != -10) || here_doc)
		remove_redirection(tml);
	return (exit_status);
}
