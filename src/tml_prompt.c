/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:58:48 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 19:21:30 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_create_uhp_line(t_ml *tml)
{
	tml->pwd = vr_get_value(tml->vars, "PWD", TRUE);
	tml->prompt = ft_strcpy(PINK, FALSE);
	tml->prompt = ft_strcat(tml->prompt, tml->user, TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, "@", TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, tml->host, TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, GREY, TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, ":", TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, WHITE, TRUE, FALSE);
	if (!ft_strcmp(tml->pwd, getenv("HOME")))
		tml->prompt = ft_strcat(tml->prompt, "~", TRUE, FALSE);
	else
		tml->prompt = ft_strcat(tml->prompt, tml->pwd, TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, "$ ", TRUE, FALSE);
	tml->prompt = ft_strcat(tml->prompt, RESET, TRUE, FALSE);
}
