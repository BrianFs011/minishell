/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:52:52 by briferre          #+#    #+#             */
/*   Updated: 2022/06/27 10:00:19 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert_char(char *new_n, int n, size_t size)
{
	new_n[size] = '\0';
	if (n >= 0)
	{
		while (size--)
		{
			new_n[size] = (n % 10) + '0';
			n /= 10;
		}
	}
	else
	{
		while (--size)
		{
			new_n[size] = (n % 10) * -1 + '0';
			n /= 10;
		}
		new_n[size] = '-';
	}
}

char	*ft_itoa(int n)
{
	int		aux;
	char	*num;
	size_t	size;

	if (n >= 0)
		size = 1;
	else
		size = 2;
	aux = n / 10;
	while (aux)
	{
		size++;
		aux /= 10;
	}
	num = (char *)malloc(size + 1);
	if (num == NULL)
		return (NULL);
	ft_convert_char(num, n, size);
	return (num);
}
