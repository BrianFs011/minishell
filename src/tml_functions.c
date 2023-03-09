/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:14:10 by briferre          #+#    #+#             */
/*   Updated: 2023/03/09 16:17:13 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_cd(t_ml *tml)
{
	if (!tml->sprt_cmd[1])
	{
		free(tml->path);
		tml->path = ft_strcpy(getenv("HOME"), FALSE);
	}
	else
	{
		if (tml->sprt_cmd[1][0] == '/')
		{
			free (tml->path);
			tml->path = ft_strcpy(tml->sprt_cmd[1], FALSE);
		}
		else
		{
			tml->path = ft_strcat(tml->path, "/", TRUE, FALSE);
			tml->path = ft_strcat(tml->path, tml->sprt_cmd[1], TRUE, FALSE);
		}
	}
	if (chdir(tml->path) != 0)
		perror("Falha ao mudar o diretório");
}

void	tml_exec(t_ml *tml, int *fd)
{
	rd_redirection(tml, fd);
	if (!((!ft_strncmp(tml->sprt_cmd[0], "./", 2))
			|| tml->sprt_cmd[0][0] == '/'))
		tml->sprt_cmd[0] = ft_strcat(ft_strcpy("/usr/bin/", FALSE),
				tml->sprt_cmd[0], TRUE, TRUE);
	if (tml->pp_quant != 0)
		pp_switch(tml);
	if (execve(tml->sprt_cmd[0], tml->sprt_cmd, tml->env) == -1)
	{
		perror("Execve");
		exit(1);
	}
}

void	tml_get_uhp(t_ml *tml)
{
	tml->user = ft_strcpy(getenv("USER"), FALSE);
	tml->host = fl_get_text("/etc/hostname");
	tml->signal = NULL;
	tml->cmd = NULL;
	tml->pp_cmd = NULL;
	tml->vars = NULL;
}

void	tml_create_uhp_line(t_ml *tml)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		tml->path = ft_strcpy(cwd, FALSE);
	else
		perror("getcwd() falhou");
	tml->info = ft_strcpy("\033[1;35m", FALSE);
	tml->info = ft_strcat(tml->info, tml->user, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "@", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, tml->host, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "\033[22;39m", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, ":", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "\033[1;90m", TRUE, FALSE);
	if (!ft_strcmp(tml->path, getenv("HOME")))
		tml->info = ft_strcat(tml->info, "~", TRUE, FALSE);
	else
		tml->info = ft_strcat(tml->info, tml->path, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "$ ", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "\033[0m", TRUE, FALSE);
}
