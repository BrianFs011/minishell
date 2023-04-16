/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:58:48 by briferre          #+#    #+#             */
/*   Updated: 2023/04/16 14:58:58 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tml_create_uhp_line(t_ml *tml)
{
	tml->path = vr_get_value(tml->vars, "PWD", TRUE);
	tml->info = ft_strcpy(PINK, FALSE);
	tml->info = ft_strcat(tml->info, tml->user, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "@", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, tml->host, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, GREY, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, ":", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, WHITE, TRUE, FALSE);
	if (!ft_strcmp(tml->path, getenv("HOME")))
		tml->info = ft_strcat(tml->info, "~", TRUE, FALSE);
	else
		tml->info = ft_strcat(tml->info, tml->path, TRUE, FALSE);
	tml->info = ft_strcat(tml->info, "$ ", TRUE, FALSE);
	tml->info = ft_strcat(tml->info, RESET, TRUE, FALSE);
}
