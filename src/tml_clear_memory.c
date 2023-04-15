/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_clear_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:11:23 by briferre          #+#    #+#             */
/*   Updated: 2023/03/20 14:51:37 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_free_uhp(t_ml *tml)
{
	ft_free(tml->user);
	ft_free(tml->host);
}

void	tml_free_sprt_cmd(t_string *string_list)
{
	int	i;

	i = -1;
	while (string_list[++i])
		free(string_list[i]);
	free(string_list);
	string_list = NULL;
}
