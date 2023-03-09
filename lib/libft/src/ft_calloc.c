/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:35:57 by briferre          #+#    #+#             */
/*   Updated: 2022/07/06 15:14:00 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*alloc;

	if ((nmemb == 18446744073709551615UL && size > 1)
		|| (size == 18446744073709551615UL && nmemb > 1))
		return (NULL);
	alloc = malloc (nmemb * size);
	if (alloc)
	{
		i = 0;
		while (i < nmemb * size)
		{
			alloc[i] = 0;
			i++;
		}
		return (alloc);
	}
	else
		return (NULL);
}
