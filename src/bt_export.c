/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:39:31 by briferre          #+#    #+#             */
/*   Updated: 2023/04/26 19:13:15 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
	export -> imprime as variaveis de ambiente
		comportamento no mini: não entra em bt_export
	export hello -> transforma uma variavel local em uma variavel de ambiente
	export hello=10 -> cria uma variavel de ambiente
*/

static t_bool	ck_var_name(t_string str)
{
	return (str && ft_isalpha(str[0]) && ft_strisalpha(str));
}

static int	local_to_env_var(t_ml *tml, t_varlist var)
{
	t_varlist	*local_var;
	t_varlist	new_var;
	int			exit_status;

	local_var = tml->local_vars;
	new_var.name = NULL;
	new_var.value = NULL;
	exit_status = 0;
	while (local_var)
	{
		if (!ft_strcmp(local_var->name, var.name))
		{
			new_var.name = ft_strcpy(var.name, FALSE);
			new_var.value = vr_get_value(tml->local_vars, var.name, TRUE);
			vr_insert(&tml->env_vars, new_var, FALSE, FALSE);
			vr_delete_node(&tml->local_vars, var);
		}
		local_var = local_var->next;
	}
	if (new_var.name)
		free(new_var.name);
	if (new_var.value)
		free(new_var.value);
	return (exit_status);
}

static int	env_var(t_ml *tml, t_varlist var)
{
	int	exit_status;

	exit_status = 0;
	if (!vr_change_value(&(tml->env_vars), var))
		vr_insert(&(tml->env_vars), var, FALSE, FALSE);
	return (exit_status);
}

int	bt_export(t_ml *tml)
{
	int			exit_status;
	t_varlist	var;

	exit_status = 0;
	var.name = NULL;
	var.value = NULL;
	var = vr_get_name_value(tml->split_cmd[1]);
	if (!ck_var_name(var.name))
	{
		ft_print_error(ft_strjoin("export: `", tml->split_cmd[1]),
			"': not a valid identifier", TRUE);
		exit_status = 1;
	}
	else
	{
		if (ft_cc(tml->cmd, '='))
			exit_status = env_var(tml, var);
		else
			exit_status = local_to_env_var(tml, var);
		if (var.name)
			free(var.name);
		if (var.value)
			free(var.value);
	}
	return (exit_status);
}
