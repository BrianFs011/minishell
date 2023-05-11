/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:29:29 by briferre          #+#    #+#             */
/*   Updated: 2023/05/10 21:02:39 by sde-cama         ###   ########.fr       */
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

static void	if_here_doc(t_ml *tml, t_string *cmd, int j, int *exit_code)
{
	if (!strcmp(cmd[j], "<<"))
	{
		if (tml->here_doc == NULL)
			tml->here_doc = rd_in_delimiter(tml, cmd[j + 1]);
		else
			tml->here_doc = ft_strrpc(tml->here_doc,
					rd_in_delimiter(tml, cmd[j + 1]), TRUE, TRUE);
		tml->redirect_in = 2;
		*exit_code = is_ctrl_c(0, 0);
	}
}

int	rd_open_here_doc(t_ml *tml)
{
	int			i;
	int			j;
	int			exit_code;
	t_string	*cmd;

	i = -1;
	tml->here_doc = NULL;
	exit_code = 0;
	while (tml->pp_cmd[++i] && exit_code == 0)
	{
		exit_code = is_ctrl_c(0, 1);
		cmd = ft_split(tml->pp_cmd[i], ' ');
		j = -1;
		while (cmd[++j] && exit_code == 0)
			if_here_doc(tml, cmd, j, &exit_code);
		tml_free_sprt_cmd(cmd);
	}
	return (exit_code);
}
