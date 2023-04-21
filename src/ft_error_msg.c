/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:22:44 by sde-cama          #+#    #+#             */
/*   Updated: 2023/04/21 14:32:46 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_print_error(char *arg, char *message, t_bool freeArg)
{
	char	*error_msg;

	if (arg != NULL)
		error_msg = ft_strjoin("minishell: ", arg);
	else
		error_msg = ft_strdup("minishell: ");
	error_msg = ft_strcat(error_msg, message, TRUE, FALSE);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (freeArg)
		free(arg);
	free(error_msg);
}
