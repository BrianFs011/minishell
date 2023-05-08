/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:09:02 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 17:35:23 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "terminal.h"

/// @brief Create a file for out
/// @param tml struct t_ml
/// @param fd addrs file descriptor
/// @return exit status
int			rd_redirection(t_ml *tml, int *fd);

/// @brief Count lines of t_string *
/// @param split struct t_string *
/// @return Lines quantity
int			count_split(t_string *split);

/// @brief Remove redirect from tml->split_cmd
/// @param tml struct t_tml
void		remove_redirection(t_ml *tml);

/// @brief Set here_doc as STDIN
/// @param here_doc type t_string
void		set_here_doc(t_string here_doc);

int			rd_open_here_doc(t_ml *tml);

int			is_ctrl_c(int value, int set);

t_string	rd_in_delimiter(t_ml *tml, t_string hd_eof);

#endif