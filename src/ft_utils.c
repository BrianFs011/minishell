/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:21:41 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 09:38:41 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strisalpha(t_string str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]))
			return (0);
	return (1);
}


