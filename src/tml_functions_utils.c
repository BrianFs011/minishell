/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:21:41 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 19:01:12 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_string	*tml_construct_env(t_ml *tml)
{
	int				i;
	t_varlist		*temp;
	t_string		*env;

	temp = tml->env_vars;
	env = malloc(sizeof(t_string) * temp->size + sizeof(t_string));
	i = -1;
	while (temp)
	{
		env[++i] = ft_strcat(temp->name,
				ft_strcat("=", temp->value, FALSE, FALSE), FALSE, TRUE);
		temp = temp->next;
	}
	env[++i] = NULL;
	return (env);
}

static t_string	*init_path(t_varlist *start)
{
	t_varlist	*temp;

	temp = start;
	while (temp && ft_strncmp(temp->name, "PATH", 4))
		temp = temp->next;
	return (ft_split(temp->value, ':'));
}

static void	loop_check(t_ml *tml, t_string *paths, int *check)
{
	t_string	temp;
	int			i;

	i = -1;
	while (paths[++i] && (*check) != 0)
	{
		temp = ft_strcat(paths[i], ft_strcat("/", tml->split_cmd[0],
					FALSE, FALSE), FALSE, TRUE);
		if (access(temp, X_OK) == 0)
		{
			tml->split_cmd[0] = ft_strrpc(tml->split_cmd[0], temp, TRUE, TRUE);
			(*check) = 0;
		}
		else
			free(temp);
	}
}

int	tml_find_exec(t_ml *tml)
{
	t_string	*paths;
	int			check;

	check = 127;
	paths = init_path(tml->env_vars);
	if (*tml->split_cmd[0] == '\0')
		exit(0);
	loop_check(tml, paths, &check);
	tml_free_sprt_cmd(paths);
	if (check)
		ft_print_error(tml->split_cmd[0], ": command not found", FALSE);
	return (check);
}
