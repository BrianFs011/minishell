/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:42:40 by sde-cama          #+#    #+#             */
/*   Updated: 2023/05/06 13:42:04 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fd_close(int fd)
{
	if (fd < 0)
		return ;
	close(fd);
}

int	fd_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		return (1);
	fd_close(oldfd);
	return (0);
}

void	ft_dup_stdin_out(t_ml *tml)
{
	tml->stdin = dup(STDIN_FILENO);
	tml->stdout = dup(STDOUT_FILENO);
}
