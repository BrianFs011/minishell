/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:21:41 by briferre          #+#    #+#             */
/*   Updated: 2023/04/21 14:17:03 by sde-cama         ###   ########.fr       */
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

int	tml_find_exec(t_ml *tml)
{
	t_string	temp;
	t_string	*paths;
	int			i;
	int			check;

	i = -1;
	check = 127;
	paths = init_path(tml->env_vars);
	while (paths[++i] && check != 0)
	{
		temp = ft_strcat(paths[i], ft_strcat("/", tml->split_cmd[0],
					FALSE, FALSE), FALSE, TRUE);
		if (access(temp, X_OK) == 0)
		{
			tml->split_cmd[0] = ft_strrpc(tml->split_cmd[0], temp, TRUE, TRUE);
			check = 0;
		}
		else
			free(temp);
	}
	tml_free_sprt_cmd(paths);
	if (check)
	{
		// printf("minishell: %s: command not found\n", tml->split_cmd[0]);
		ft_putendl_fd("minishell: command not found", STDERR_FILENO);
	}
	return (check);
}
