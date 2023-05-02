/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:09:52 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 16:19:04 by briferre         ###   ########.fr       */
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
		tml->redirect_out = 1;
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
	if (fd_dup2(fd_pipe[0], STDIN_FILENO))
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
		if (fd_dup2(*fd, STDIN_FILENO))
			return (tml_set_pexit_status("dup2", 1));
		tml->redirect_in = 1;
	}
	if (!strcmp(tml->split_cmd[*i], "<<"))
	{
		rd_in_delimiter(tml, i);
		*fd = -2;
		tml->redirect_in = 1;
	}
	return (0);
}

int	count_split(t_string *split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
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
	while (tml->split_cmd[++i])
	{
		if (!ft_strcmp(tml->split_cmd[i], ">>") || !ft_strcmp(tml->split_cmd[i], ">") || !ft_strcmp(tml->split_cmd[i], "<") || !ft_strcmp(tml->split_cmd[i], "<<"))
		{
			if (tml->split_cmd[i + 1])
				i++;
		}
		else
			split[++j] = ft_strcpy(tml->split_cmd[i], FALSE);
	}
	if (++j <= i)
		split[j] = NULL;
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

int	rd_redirection(t_ml *tml, int *fd)
{
	int			i;
	int			exit_status;

	// i = -1;
	// while (tml->split_cmd[++i])
	// 	printf("\033[32m redirect\033[0m: %s\n", tml->split_cmd[i]);
	// printf("\033[33m redirect\033[0m: %d\n", count_split(tml->split_cmd));
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
	// remover o redirecionamento
	if (exit_status == 0 && (*fd) != -10)
		remove_redirection(tml);
	// i = -1;
	// while (tml->split_cmd[++i])
	// 	printf("\033[31m redirect\033[0m: %s\n", tml->split_cmd[i]);
	return (exit_status);
}

// if (*fd != -10)
// {
// 	printf("\033[34m redirect\033[0m: %s\n", tml->split_cmd[i]);
// 	// free(tml->split_cmd[--i]);
// 	// tml->split_cmd[i] = NULL;
// 	// free(tml->split_cmd[++i]);
// 	// tml->split_cmd[i] = NULL;
// }
