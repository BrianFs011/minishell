/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:43:43 by briferre          #+#    #+#             */
/*   Updated: 2022/06/25 11:04:36 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		cmp;

	cmp = 0;
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		cmp += ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (cmp != 0)
			break ;
		i++;
	}
	return (cmp);
}
