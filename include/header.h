/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:27:47 by briferre          #+#    #+#             */
/*   Updated: 2023/04/16 18:06:32 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minishell.h"
# include "variables.h"
# include "terminal.h"
# include "redirection.h"
# include "pipes.h"
# include "sigaction.h"
# include "check_cmd.h"
# include "libfte.h"
# include "builtins.h"

/// @brief Create a new process
/// @param pid Pid from fork function
/// @param tml Struct t_ml
void		fk_call_new_process(t_ml *tml);

/// @brief Wait for processes to be finished
/// @param tml Struct t_ml that holds a list of pids
void		fk_wait_execs(t_ml *tml);

/// @brief Get text from file text
/// @param path Path from file text
/// @return t_string with text
t_string	fl_get_text(t_string path);

#endif