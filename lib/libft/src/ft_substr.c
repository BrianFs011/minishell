/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:14:18 by briferre          #+#    #+#             */
/*   Updated: 2022/07/06 13:47:26 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_s;
	size_t		i;

	if (!s)
		return (NULL);
	if (start < (unsigned int)ft_strlen((char *)s))
		i = ft_strlen((char *)s) - start + 1;
	if (start >= (unsigned int)ft_strlen((char *)s))
		i = 1;
	if (i > len)
		i = len + 1;
	new_s = (char *)malloc(sizeof(char) * i);
	if (!new_s)
		return (NULL);
	if (i - 1 == 0)
		new_s[0] = '\0';
	else
		ft_strlcpy(new_s, &s[start], i);
	return (new_s);
}
// {
// 	size_t		i;
// 	size_t		j;
// 	char		*new_s;

// 	i = (size_t)ft_strlen((char *)s);
// 	if (len < i)
// 		i = len;
// 	if (start > i)
// 		i = 0;
// 	new_s = (char *)malloc((sizeof(char) * i) + 1);
// 	if (!new_s)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (i >= start && j < len)
// 		{
// 			new_s[j] = s[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_s[j] = '\0';
// 	return (new_s);
// }
