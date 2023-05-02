/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:28:40 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 18:11:27 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	*ft_strvchr(t_string string, char c)
{
	int	i;
	int	j;
	int	cont;
	int	*vector;

	i = -1;
	cont = 0;
	while (string[++i])
		if (string[i] == c)
			cont++;
	vector = malloc(sizeof(int) * cont + sizeof(int));
	i = -1;
	j = 0;
	while (string[++i])
		if (string[i] == c)
			vector[++j] = i;
	vector[0] = ++j;
	return (vector);
}

int	ft_cc(t_string text, char character)
{
	int	i;
	int	cont;

	i = -1;
	cont = 0;
	while (text[++i])
		if (text[i] == character)
			cont++;
	return (cont);
}
