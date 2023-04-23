/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_llong_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:41:16 by briferre          #+#    #+#             */
/*   Updated: 2023/04/22 19:53:05 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ck_max(t_string num, int size_num)
{
	int			i;
	int			size_llongmax;
	t_string	llongmax;

	i = -1;
	llongmax = "9223372036854775807";
	size_llongmax = ft_strlen(llongmax);
	if (size_num == size_llongmax)
	{
		i = -1;
		while (num[++i])
		{
			if (llongmax[i] - num[i] < 0)
				return (0);
		}
	}
	else if (size_num > size_llongmax && num[0] != '-')
		return (0);
	return (1);
}

static int	ck_min(t_string num, int size_num)
{
	int			i;
	int			size_llongmin;
	t_string	llongmin;

	i = -1;
	llongmin = "-9223372036854775808";
	size_llongmin = ft_strlen(llongmin);
	if (size_num == size_llongmin)
	{
		while (num[++i])
			if (llongmin[i] - num[i] < 0)
				return (0);
	}
	else if (size_num > size_llongmin)
		return (0);
	return (1);
}

int	ck_isllongint(t_string num)
{
	int	size_num;
	int	r;

	size_num = ft_strlen(num);
	r = ck_min(num, size_num);
	if (r)
		r = ck_max(num, size_num);
	return (r);
}
