/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:09:02 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 18:31:33 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "terminal.h"

/// @brief Create a file for out
/// @param tml struct t_ml
/// @param fd addrs file descriptor
/// @return exit status
int		rd_redirection(t_ml *tml, int *fd);

/// @brief Save an html structure in a static variable
/// @param tml struct t_ml
/// @param save condition that defines whether or not to save the address
/// @return the saved address
t_ml	*save_point(t_ml *tml, t_bool save);

/// @brief Count lines of t_string *
/// @param split struct t_string *
/// @return Lines quantity
int		count_split(t_string *split);

/// @brief Remove redirect from tml->split_cmd
/// @param tml struct t_tml
void	remove_redirection(t_ml *tml);

#endif