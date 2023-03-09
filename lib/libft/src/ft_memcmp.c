/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:49:01 by briferre          #+#    #+#             */
/*   Updated: 2022/06/24 11:53:28 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*aux_s1;
	unsigned char	*aux_s2;
	size_t			i;
	int				cmp;

	cmp = 0;
	i = 0;
	aux_s1 = (unsigned char *)s1;
	aux_s2 = (unsigned char *)s2;
	while (i < n)
	{
		cmp += ((int)aux_s1[i] - (int)aux_s2[i]);
		if (cmp != 0)
			break ;
		i++;
	}
	return (cmp);
}
