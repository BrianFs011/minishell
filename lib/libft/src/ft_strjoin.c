/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:15:21 by briferre          #+#    #+#             */
/*   Updated: 2022/06/27 10:01:24 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cont_string(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*concatenation;

	i = cont_string((char *)s1);
	j = cont_string((char *)s2);
	concatenation = malloc(sizeof(char) * (i + j + 1));
	if (!concatenation || !s1 || !s2)
		return ((void *)0);
	i = 0;
	while (s1[i])
	{
		concatenation[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		concatenation[i + j] = s2[j];
		j++;
	}
	concatenation[i + j] = '\0';
	return (concatenation);
}
