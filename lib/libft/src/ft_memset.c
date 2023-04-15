/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 02:55:02 by briferre          #+#    #+#             */
/*   Updated: 2022/04/10 00:30:15 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int				i;
	unsigned char	*aux;

	i = 0;
	aux = (unsigned char *)s;
	while (i < (int)n)
	{
		aux[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
