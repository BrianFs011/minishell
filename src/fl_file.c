/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:47:52 by briferre          #+#    #+#             */
/*   Updated: 2023/02/15 18:30:11 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_string	fl_get_text(t_string path)
{
	int			fd;
	int			size_buf;
	char		empt[1];
	t_string	buf;

	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
		return (NULL);
	size_buf = 0;
	while (read(fd, empt, 1) != 0)
		size_buf++;
	buf = malloc (sizeof(char) * size_buf + 1);
	lseek(fd, 0, SEEK_SET);
	size_buf = 0;
	while (read(fd, &buf[size_buf], 1) != 0)
		size_buf++;
	buf[size_buf - 1] = '\0';
	close(fd);
	return (buf);
}
