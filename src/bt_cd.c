/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:00:21 by briferre          #+#    #+#             */
/*   Updated: 2023/05/03 14:15:04 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	no_pwd(t_ml *tml, t_varlist *old_pwd)
{
	t_string	message;

	message = ft_strcat("minishell: cd : ", tml->split_cmd[1], FALSE, FALSE);
	perror(message);
	free(message);
	free(old_pwd->name);
	free(old_pwd->value);
	return (1);
}

static int	check_cd(t_ml *tml, t_varlist *new_pwd, t_varlist *old_pwd)
{
	if (chdir(tml->pwd) != 0)
		return (no_pwd(tml, old_pwd));
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

static int	cd_error(t_ml *tml, int error)
{
	ft_print_error(tml->split_cmd[0], ": too many arguments", FALSE);
	return (error);
}

int	bt_cd(t_ml *tml)
{
	t_varlist	new_pwd;
	t_varlist	old_pwd;
	int			exit_status;

	if (tml->split_cmd[1] && tml->split_cmd[2])
		return (cd_error(tml, 1));
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
