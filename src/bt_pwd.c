/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:31:24 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 07:31:46 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
