/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:55:11 by briferre          #+#    #+#             */
/*   Updated: 2022/07/10 09:23:28 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		lenght;
	int		size;
	char	*dest;

	lenght = (ft_strlen(s1) - 1);
	start = 0;
	size = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (lenght > start && ft_strchr(set, s1[lenght]))
		lenght--;
	if (start <= lenght)
		dest = malloc((++lenght - start) + 1);
	else
		dest = malloc(1);
	if (!dest)
		return (NULL);
	while (start < lenght)
		dest[size++] = s1[start++];
	dest[size] = '\0';
	return (dest);
}
