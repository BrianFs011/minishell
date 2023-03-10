/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:14:10 by briferre          #+#    #+#             */
/*   Updated: 2023/03/10 16:45:49 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_cd(t_ml *tml)
{
	//add convert ~ in HOME
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

t_string	*construct_env(t_ml *tml)
{
	t_vars		*temp;
	t_string	*env;
	int			i;

	temp = tml->vars;
	env = malloc(sizeof(t_string) * temp->size);
	i = -1;
	while (temp)
	{
		env[++i] = ft_strcat(temp->name,
				ft_strcat("=", temp->value, FALSE, FALSE), FALSE, TRUE);
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}

void	tml_exec(t_ml *tml, int *fd)
{
	int			i;
	t_string	path_test;

	rd_redirection(tml, fd);
	if (!((!ft_strncmp(tml->sprt_cmd[0], "./", 2))
			|| tml->sprt_cmd[0][0] == '/'))
	{
		i = -1;
		while (tml->paths[++i])
		{
			path_test = ft_strcat(tml->paths[i],
					ft_strcat("/", tml->sprt_cmd[0],
						FALSE, FALSE), FALSE, TRUE);
			if (access(path_test, X_OK) == 0)
			{
				free(tml->sprt_cmd[0]);
				tml->sprt_cmd[0] = ft_strcpy(path_test, TRUE);
				break ;
			}
			else
				free(path_test);
		}
	}
	if (tml->pp_quant != 0)
		pp_switch(tml);
	tml->env = construct_env(tml);
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
