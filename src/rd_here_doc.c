/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:29:29 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 11:39:15 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

static t_string	rd_in_delimiter(t_ml *tml, t_string hd_eof)
{
	t_string	temp;
	t_string	temp2;
	int			condition;

	temp2 = NULL;
	temp = NULL;
	condition = 1;
	while (condition)
	{
		temp = readline("> ");
		condition = ft_strcmp(temp, hd_eof);
		if (condition)
		{
			temp = vr_descompress(tml, temp);
			if (temp2)
				temp2 = ft_strcat(temp2, temp, TRUE, FALSE);
			else
				temp2 = ft_strcpy(temp, FALSE);
			temp2 = ft_strcat(temp2, "\n", TRUE, FALSE);
		}
		free(temp);
	}
	return (temp2);
}

void	rd_open_here_doc(t_ml *tml)
{
	int			i;
	int			j;
	t_string	*cmd;

	i = -1;
	tml->here_doc = NULL;
	while (tml->pp_cmd[++i])
	{
		cmd = ft_split(tml->pp_cmd[i], ' ');
		j = -1;
		while (cmd[++j])
		{
			if (!strcmp(cmd[j], "<<"))
			{
				if (tml->here_doc == NULL)
					tml->here_doc = rd_in_delimiter(tml, cmd[j + 1]);
				else
					tml->here_doc = ft_strrpc(tml->here_doc,
							rd_in_delimiter(tml, cmd[j + 1]), TRUE, TRUE);
				tml->redirect_in = 1;
			}
		}
		tml_free_sprt_cmd(cmd);
	}
}
