/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:21:41 by briferre          #+#    #+#             */
/*   Updated: 2023/04/22 20:14:48 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_bool	ft_strisalpha(t_string str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]))
			return (FALSE);
	return (TRUE);
}

int	ft_isdigit_plus(int a)
{
	return (ft_isdigit(a) || a == '-' || a == '+');
}

int	ft_foreach(t_string string, int (f)(int))
{
	int		i;

	i = -1;
	while (string[++i])
	{
		if (!f(string[i]))
			return (i);
	}
	return (-1);
}
