/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:44:46 by briferre          #+#    #+#             */
/*   Updated: 2022/06/24 18:54:14 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argument)
{
	int	i;

	if ((argument >= 'a' && argument <= 'z')
		|| (argument >= 'A' && argument <= 'Z')
		|| (argument >= '0' && argument <= '9'))
		i = 1;
	else
		i = 0;
	return (i);
}
