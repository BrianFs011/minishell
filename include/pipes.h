/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:10:39 by briferre          #+#    #+#             */
/*   Updated: 2023/05/07 13:17:10 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "terminal.h"

/// @brief Switch STDIN_FILENO for pipe[0] and STDOUT_FILENO for pipe[1]
/// @param tml struct t_ml
void	pp_switch(t_ml *tml, int *fd);

/// @brief Called when have one or more pipes
/// @param tml struct t_ml
void		tml_scroll_pipe_list(t_ml *tml);

void		pp_error(t_ml *tml, int *error);

#endif