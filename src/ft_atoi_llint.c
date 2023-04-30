/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_llint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:55:05 by briferre          #+#    #+#             */
/*   Updated: 2023/04/22 20:13:07 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	check_spaces_sign(const char **ptr, int *sign)
{
	while (**ptr == ' ')
			(*ptr)++;
	if (**ptr == '-')
	{
		(*sign) = -1;
		(*ptr)++;
	}
	else if (**ptr == '+')
		(*ptr)++;
}

long long int	ft_atoi_llint(const char *str)
{
	long long int	num;
	int				sign;
	const char		*ptr = str;

	num = 0;
	sign = 1;
	check_spaces_sign(&ptr, &sign);
	while (*ptr)
	{
		if (num > (LLONG_MAX - (*ptr - '0')) / 10)
		{
			errno = ERANGE;
			if (sign == -1)
				return (LLONG_MIN);
			else
				return (LLONG_MAX);
		}
		num = num * 10 + (*ptr - '0');
		ptr++;
	}
	return (num * sign);
}
