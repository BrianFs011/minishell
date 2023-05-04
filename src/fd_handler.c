/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:42:40 by sde-cama          #+#    #+#             */
/*   Updated: 2023/05/02 18:05:04 by briferre         ###   ########.fr       */
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
