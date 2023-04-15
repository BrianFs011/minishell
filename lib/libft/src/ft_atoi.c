/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:05:27 by briferre          #+#    #+#             */
/*   Updated: 2023/01/03 22:13:08 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check_spaces(char *str, int i)
{
	if (str[i] == ' '
		|| str[i] == '\n'
		|| str[i] == '\t'
		|| str[i] == '\r'
		|| str[i] == '\f'
		|| str[i] == '\v')
		return (1);
	return (0);
}

static int	ft_check_number(char *str, int i)
{
	if (str[i] >= '0' && str[i] <= '9')
		i = 1;
	else
		i = 0;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	convert;
	int	sinal;

	i = 0;
	sinal = 0;
	while ((ft_check_spaces((char *)str, i)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sinal = -1;
		i++;
	}
	convert = 0;
	while (ft_check_number((char *)str, i) && str[i])
	{
		convert = (convert * 10) + (str[i] - 48);
		i++;
	}
	if (sinal == -1)
		convert *= -1;
	return (convert);
}
