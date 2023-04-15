/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:17:04 by briferre          #+#    #+#             */
/*   Updated: 2022/04/12 03:16:39 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*aux_src;
	unsigned char	*aux_dest;

	if (!dest && !src)
		return (NULL);
	i = 0;
	aux_src = (unsigned char *)src;
	aux_dest = (unsigned char *)dest;
	if (aux_dest > aux_src)
		while (n-- > 0)
			aux_dest[n] = aux_src[n];
	else
	{
		while (i < n)
		{
			aux_dest[i] = aux_src[i];
			i++;
		}
	}
	return (dest);
}
