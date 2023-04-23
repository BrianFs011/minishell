/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:49 by briferre          #+#    #+#             */
/*   Updated: 2023/04/23 14:36:09 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ck_check(t_ml *tml)
{
	int	exit_status;

	exit_status = ck_quotes(tml);
	if (exit_status == 0)
		exit_status = ck_redictions(tml);
	// printf("%d\n", exit_status);
	return (exit_status);
}
