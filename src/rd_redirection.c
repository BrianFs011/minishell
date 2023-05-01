/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/05/01 11:28:11 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	rd_out(t_ml *tml, int *fd, int *i)
{
	int	oflag;

	if (!strcmp(tml->split_cmd[*i], ">") || !strcmp(tml->split_cmd[*i], ">>"))
	{
		// printf("\033[35msprt_cmd\033[0m: %s|\n", tml->split_cmd[*i]);
		oflag = O_CREAT | O_WRONLY | O_TRUNC;
		if (!strcmp(tml->split_cmd[*i], ">"))
			*fd = open (tml->split_cmd[++(*i)], oflag, 0644);//pq 0644? - não deveria ser 0664?
		oflag = O_WRONLY | O_APPEND | O_CREAT;
		if (!strcmp(tml->split_cmd[*i], ">>"))
			*fd = open (tml->split_cmd[++(*i)], oflag, 0644);
		if (*fd == -1)
			return (tml_set_pexit_status(tml->split_cmd[*i], 1));
		if (fd_dup2(*fd, STDOUT_FILENO))
			return (tml_set_pexit_status("dup2", 1));
	}
	return (0);
}

//desaloca a memória sem passar pelo fluxo de saida do programa
t_ml	*save_point(t_ml *tml, t_bool save)
{
	static t_ml	*tml_save;

	if (save)
		tml_save = tml;
	return (tml_save);
}

void	rd_in_delimiter(t_ml *tml, int *i)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		tml_set_pexit_status("pipe", EXIT_FAILURE);
	(*i)++;
	tml->split_cmd[*i] = ft_strcat(tml->split_cmd[*i], "\n", TRUE, FALSE);
	save_point(tml, TRUE);
	while (ft_strcmp(tml->cmd, tml->split_cmd[*i]))
	{
		free(tml->cmd);
		tml->cmd = NULL;
		tml->cmd = readline("> ");
		tml->cmd = ft_strcat(tml->cmd, "\n", TRUE, FALSE);
		if (ft_strcmp(tml->cmd, tml->split_cmd[*i]))
			write(fd_pipe[1], tml->cmd, ft_strlen(tml->cmd));
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		tml_set_pexit_status("dup2", EXIT_FAILURE);
	close(fd_pipe[0]);
}

int	rd_in(t_ml *tml, int *fd, int *i)
{
	if (!strcmp(tml->split_cmd[*i], "<"))
	{
		*fd = open(tml->split_cmd[++(*i)], O_RDONLY, 0644);
		if (*fd == -1)
			return (tml_set_pexit_status("missing", 1));
		if (dup2(*fd, STDIN_FILENO) == -1)
			return (tml_set_pexit_status("dup2", 1));
	}
	if (!strcmp(tml->split_cmd[*i], "<<"))
	{
		rd_in_delimiter(tml, i);
		*fd = -2;
	}
	return (0);
}

int	rd_redirection(t_ml *tml, int *fd)
{
	int	i;
	int	exit_status;

	i = -1;
	exit_status = 0;
	while (tml->split_cmd[++i])
	{
		exit_status = rd_in(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
		exit_status = rd_out(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
		if (*fd != -10)
		{
			free(tml->split_cmd[--i]);
			tml->split_cmd[i] = NULL;
			free(tml->split_cmd[++i]);
			tml->split_cmd[i] = NULL;
		}
	}
	return (exit_status);
}
