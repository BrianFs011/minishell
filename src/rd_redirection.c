/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 19:23:32 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	rd_out(t_ml *tml, int *fd, int *i)
{
	int			oflag;

	if (!strcmp(tml->sprt_cmd[*i], ">") || !strcmp(tml->sprt_cmd[*i], ">>"))
	{
		// printf("\033[35msprt_cmd\033[0m: %s|\n", tml->sprt_cmd[*i]);
		oflag = O_CREAT | O_WRONLY | O_TRUNC;
		if (!strcmp(tml->sprt_cmd[*i], ">"))
			*fd = open (tml->sprt_cmd[++(*i)], oflag, 0644);
		oflag = O_WRONLY | O_APPEND | O_CREAT;
		if (!strcmp(tml->sprt_cmd[*i], ">>"))
			*fd = open (tml->sprt_cmd[++(*i)], oflag, 0644);
		if (*fd == -1)
			return (tml_set_pexit_status("open", 1));
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (tml_set_pexit_status("dup2", 1));
	}
	return (0);
}

//desaloca a memória sem passar pelo fluxo de saida do programa
void	free_tml(t_ml *tml, t_bool save, t_bool free)
{
	static t_ml	*tml_save;

	if (save)
		tml_save = tml;
	if (free)
	{
		vr_delete(&tml_save->cmd_vars);
		ft_free(tml_save->pwd);
		ft_free(tml_save->prompt);
		ft_free(tml_save->cmd);
		tml_free_uhp(tml_save);
		vr_delete(&tml_save->assigned);
		vr_delete(&tml_save->vars);
		rl_clear_history();
	}
}

void	rd_in_delimiter(t_ml *tml, int *i)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		tml_set_pexit_status("pipe", EXIT_FAILURE);
	(*i)++;
	tml->sprt_cmd[*i] = ft_strcat(tml->sprt_cmd[*i], "\n", TRUE, FALSE);
	free_tml(tml, 1, 0);
	while (ft_strcmp(tml->cmd, tml->sprt_cmd[*i]) && g_pid == G_CHILD)
	{
		free(tml->cmd);
		tml->cmd = NULL;
		tml->cmd = readline("> ");
		tml->cmd = ft_strcat(tml->cmd, "\n", TRUE, FALSE);
		if (ft_strcmp(tml->cmd, tml->sprt_cmd[*i]))
			write(fd_pipe[1], tml->cmd, ft_strlen(tml->cmd));
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		tml_set_pexit_status("dup2", EXIT_FAILURE);
	close(fd_pipe[0]);
}

int	rd_in(t_ml *tml, int *fd, int *i)
{
	if (!strcmp(tml->sprt_cmd[*i], "<"))
	{
		*fd = open(tml->sprt_cmd[++(*i)], O_RDONLY, 0644);
		if (*fd == -1)
			return (tml_set_pexit_status("open", 1));
		if (dup2(*fd, STDIN_FILENO) == -1)
			return (tml_set_pexit_status("dup2", 1));
	}
	if (!strcmp(tml->sprt_cmd[*i], "<<"))
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
	while (tml->sprt_cmd[++i])
	{
		exit_status = rd_in(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
		exit_status = rd_out(tml, fd, &i);
		if (exit_status != 0)
			return (exit_status);
		if (*fd != -10)
		{
			free(tml->sprt_cmd[--i]);
			tml->sprt_cmd[i] = NULL;
			free(tml->sprt_cmd[++i]);
			tml->sprt_cmd[i] = NULL;
		}
	}
	return (exit_status);
}
