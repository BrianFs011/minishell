/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_builtins01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:50:23 by briferre          #+#    #+#             */
/*   Updated: 2023/04/07 12:10:32 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	bt_exit(t_ml *tml)
{
	if (!ft_strcmp(tml->sprt_cmd[0], "exit"))
	{
		if (tml->sprt_cmd[2] == NULL)
			tml->running = FALSE;
		else
			printf("bash: exit: too many arguments\n");
	}
	return (0);
}

int	bt_call_cd(t_ml *tml)
{
	return (bt_cd(tml));
}

int	bt_call_echo(t_string *splt)
{
	return (bt_echo(splt));
}

int	bt_pwd(t_ml *tml)
{
	t_string	name;
	t_string	value;

	name = ft_strcpy("PWD", FALSE);
	value = vr_get_value(tml->vars, name, true);
	printf("%s\n", value);
	free(value);
	free(name);
	return (0);
}
