/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:12:49 by briferre          #+#    #+#             */
/*   Updated: 2023/04/30 12:32:50 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ck_check(t_ml *tml)
{
	int	exit_status;

	exit_status = ck_quotes(tml);
	if (exit_status == 0)
		exit_status = ck_redictions(tml);
	return (exit_status);
}
