/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:29:29 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 16:22:04 by briferre         ###   ########.fr       */
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

static int	is_ctrl_c(int value, int set)
{
	static int	x;

	if (set)
		x = value;
	return (x);
}

void	handle(int sig)
{
	(void)sig;
	is_ctrl_c(130, 1);
}

static t_string	rd_in_delimiter(t_ml *tml, t_string hd_eof)
{
	t_string	temp;
	t_string	temp2;
	int			condition;

	temp2 = NULL;
	temp = NULL;
	condition = 1;
	signal(SIGINT, handle);
	rl_getc_function = getc;
	while (condition)
	{
		if (condition == 0)
			break ;
		temp = readline("> ");
		if (temp)
		{
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
		else if (!temp && is_ctrl_c(0, 0) == 0)
		{
			t_string	error;

			error = ft_strcat("here-document",
					" delimited by end-of-file (wanted `", FALSE, FALSE);
			error = ft_strcat(error, hd_eof, TRUE, FALSE);
			error = ft_strcat(error, "')", TRUE, FALSE);
			ft_print_error(NULL, error, FALSE);
			free(error);
			condition = 0;
			tml_exit_status(&tml->local_vars, 130, FALSE);
		}
		else if (!temp && is_ctrl_c(0, 0) == 130)
			condition = 0;
	}
	rl_getc_function = rl_getc;
	return (temp2);
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
				exit_code = is_ctrl_c(0, 0);
			}
		}
		tml_free_sprt_cmd(cmd);
	}
	return (exit_code);
}
