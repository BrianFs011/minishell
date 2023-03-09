/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:57:51 by briferre          #+#    #+#             */
/*   Updated: 2022/06/28 14:53:08 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	size_big;
	size_t	size_little;
	size_t	size;

	size_big = ft_strlen((char *)big);
	size_little = ft_strlen((char *)little);
	if (size_little == 0)
		return ((char *)big);
	else if (size_little > size_big)
		return (NULL);
	if (size_big > len)
		size = len;
	else
		size = size_big;
	while (size_little <= size)
	{
		if (!ft_strncmp(big, little, size_little))
			return ((char *)big);
		big++;
		size--;
	}
	return (NULL);
}
