/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:21:41 by briferre          #+#    #+#             */
/*   Updated: 2023/04/07 10:24:48 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_string	*tml_construct_env(t_ml *tml)
{
	int				i;
	t_varlist		*temp;
	t_string		*env;

	temp = tml->vars;
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

int	tml_find_exec(t_ml *tml)
{
	t_string	temp;
	int			i;
	int			check;

	i = -1;
	check = 127;
	while (tml->paths[++i])
	{
		temp = ft_strcat(tml->paths[i],
				ft_strcat("/", tml->sprt_cmd[0],
					FALSE, FALSE), FALSE, TRUE);
		if (access(temp, X_OK) == 0)
		{

			free(tml->sprt_cmd[0]);
			tml->sprt_cmd[0] = ft_strcpy(temp, TRUE);
			check = 0;
			break ;
		}
		else
			free(temp);
	}
	if (check)
		printf("minishell: %s: command not found\n", tml->sprt_cmd[0]);
	return (check);
}
