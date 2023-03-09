/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 03:21:43 by briferre          #+#    #+#             */
/*   Updated: 2022/07/06 14:26:45 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		len;
	size_t		len_src;

	i = 0;
	len = ft_strlen((char *)src);
	len_src = ft_strlen(dest);
	if (!dest && size == 0)
		return (len);
	if (size <= len_src)
		return (len + size);
	else
		len += len_src;
	while (src[i] != '\0' && len_src < size - 1)
	{
		dest[len_src] = src[i];
		i++;
		len_src++;
	}
	dest[len_src] = '\0';
	return (len);
}
