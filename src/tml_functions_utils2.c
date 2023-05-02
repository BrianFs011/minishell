/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tml_functions_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:21:41 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 19:01:01 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_folder(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
		return (TRUE);
	return (FALSE);
}

int	tml_check_access(t_ml *tml)
{
	if (is_folder(tml->split_cmd[0]))
	{
		ft_print_error(ft_strcat(tml->split_cmd[0], ": ", FALSE, FALSE),
			"Is a directory", TRUE);
		return (126);
	}
	if ((access(tml->split_cmd[0], X_OK)))
	{
		ft_print_error (ft_strcat(tml->split_cmd[0], ": ", FALSE, FALSE),
			strerror(errno), TRUE);
		if (errno == ENOENT)
			return (127);
		if (errno == EACCES)
			return (126);
	}
	return (0);
}
