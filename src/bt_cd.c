/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:00:21 by briferre          #+#    #+#             */
/*   Updated: 2023/04/22 11:36:53 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_cd(t_ml *tml, t_varlist *new_pwd, t_varlist *old_pwd)
{
	t_string	message;

	if (chdir(tml->pwd) != 0)
	{
		message = ft_strcat("minishell: cd : ",
				tml->split_cmd[1], FALSE, FALSE);
		perror(message);
		free(message);
		free(old_pwd->name);
		free(old_pwd->value);
		return (1);
	}
	else
	{
		getcwd(tml->pwd, ft_strlen(tml->pwd));
		new_pwd->value = ft_strcpy(tml->pwd, FALSE);
		vr_update_insert(&tml->env_vars, *new_pwd);
		if (!vr_change_value(&tml->env_vars, *old_pwd))
			vr_update_insert(&tml->env_vars, *old_pwd);
		else
		{
			free(old_pwd->name);
			free(old_pwd->value);
		}
	}
	return (0);
}

int	bt_cd(t_ml *tml)
{
	t_varlist	new_pwd;
	t_varlist	old_pwd;
	int			exit_status;

	if (tml->split_cmd[2])
	{
		ft_print_error(tml->split_cmd[0], ": too many arguments", FALSE);
		return (1);
	}
	new_pwd.name = ft_strcpy("PWD", FALSE);
	old_pwd.name = ft_strcpy("OLDPWD", FALSE);
	old_pwd.value = ft_strcpy(tml->pwd, FALSE);
	if (!tml->split_cmd[1])
		tml->pwd = ft_strrpc(tml->pwd,
				vr_get_value(tml->env_vars, "HOME", TRUE), TRUE, TRUE);
	else
	{
		if (tml->split_cmd[1][0] == '/')
			tml->pwd = ft_strrpc(tml->pwd, tml->split_cmd[1], TRUE, FALSE);
		else
			tml->pwd = ft_strcat(tml->pwd,
					ft_strcat("/", tml->split_cmd[1], FALSE, FALSE),
					TRUE, TRUE);
	}
	exit_status = check_cd(tml, &new_pwd, &old_pwd);
	free(new_pwd.name);
	return (exit_status);
}
