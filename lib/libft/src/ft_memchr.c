/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:54:35 by briferre          #+#    #+#             */
/*   Updated: 2022/06/24 19:31:27 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux;
	unsigned char	aux_c;

	aux = (unsigned char *)s;
	aux_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*aux == aux_c)
			return (aux);
		aux++;
		i++;
	}
	return ((void *)0);
}
