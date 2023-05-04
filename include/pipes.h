/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:10:39 by briferre          #+#    #+#             */
/*   Updated: 2023/05/03 20:28:16 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "terminal.h"

/// @brief Create a array of pipe[2]
/// @param tml struct t_ml
void		pp_linked_pipes(t_ml *tml);

/// @brief Delete array of pipe[2]
/// @param tml struct t_ml
void		pp_delete_linked_pipes(t_ml *tml);

/// @brief Switch STDIN_FILENO for pipe[0] and STDOUT_FILENO for pipe[1]
/// @param tml struct t_ml
void		pp_switch(t_ml *tml);

/// @brief Called when have one or more pipes
/// @param tml struct t_ml
void		tml_scroll_pipe_list(t_ml *tml);

void		pp_error(t_ml *tml, int *error);

#endif