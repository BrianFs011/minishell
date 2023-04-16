/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:09:02 by briferre          #+#    #+#             */
/*   Updated: 2023/04/15 11:48:14 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "terminal.h"

/// @brief Create a file for out
/// @param tml struct t_ml
/// @param fd addrs file descriptor
/// @return exit status
int	rd_redirection(t_ml *tml, int *fd);

#endif