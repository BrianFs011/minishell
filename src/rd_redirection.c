/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/03/07 17:44:30 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	rd_out(t_ml *tml, int *fd, int *i)
{
	int	oflag;

	if (!strcmp(tml->sprt_cmd[*i], ">") || !strcmp(tml->sprt_cmd[*i], ">>"))
	{
		oflag = O_CREAT | O_WRONLY | O_TRUNC;
		if (!strcmp(tml->sprt_cmd[*i], ">"))
			*fd = open (tml->sprt_cmd[++(*i)], oflag, 0644);
		oflag = O_WRONLY | O_APPEND | O_CREAT;
		if (!strcmp(tml->sprt_cmd[*i], ">>"))
			*fd = open (tml->sprt_cmd[++(*i)], oflag, 0644);
		if (*fd == -1)
			ft_error("open", EXIT_FAILURE);
		if (dup2(*fd, STDOUT_FILENO) == -1)
			ft_error("dup2", EXIT_FAILURE);
	}
}

void	rd_in_delimiter(t_ml *tml, int *fd, int *i)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ft_error("pipe", EXIT_FAILURE);
	(*i)++;
	tml->sprt_cmd[*i] = ft_strcat(tml->sprt_cmd[*i], "\n", TRUE, FALSE);
	while (ft_strcmp(tml->cmd, tml->sprt_cmd[*i]))
	{
		free(tml->cmd);
		tml->cmd = readline("> ");
		tml->cmd = ft_strcat(tml->cmd, "\n", TRUE, FALSE);
		if (ft_strcmp(tml->cmd, tml->sprt_cmd[*i]))
			write(fd_pipe[1], tml->cmd, ft_strlen(tml->cmd));
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		ft_error("dup2", EXIT_FAILURE);
	*fd = -2;
	close(fd_pipe[0]);
}

void	rd_in(t_ml *tml, int *fd, int *i)
{
	if (!strcmp(tml->sprt_cmd[*i], "<"))
	{
		*fd = open(tml->sprt_cmd[++(*i)], O_RDONLY, 0644);
		if (*fd == -1)
			ft_error("open", EXIT_FAILURE);
		if (dup2(*fd, STDIN_FILENO) == -1)
			ft_error("dup2", EXIT_FAILURE);
	}
	if (!strcmp(tml->sprt_cmd[*i], "<<"))
		rd_in_delimiter(tml, fd, i);
}

void	rd_redirection(t_ml *tml, int *fd)
{
	int	i;

	i = -1;
	while (tml->sprt_cmd[++i])
	{
		rd_in(tml, fd, &i);
		rd_out(tml, fd, &i);
		if (*fd != -10)
		{
			free(tml->sprt_cmd[--i]);
			tml->sprt_cmd[i] = NULL;
			free(tml->sprt_cmd[++i]);
			tml->sprt_cmd[i] = NULL;
		}
	}
}
