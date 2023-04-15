/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:26:50 by briferre          #+#    #+#             */
/*   Updated: 2022/07/10 09:20:15 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*ret;

	str = (char *)s;
	ret = 0;
	if ((char)c == '\0')
		return (&str[ft_strlen(str)]);
	while (*str)
	{
		if (*str == (char)c)
			ret = str;
		str++;
	}
	return (ret);
}
