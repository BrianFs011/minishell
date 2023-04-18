/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:15:48 by briferre          #+#    #+#             */
/*   Updated: 2023/04/17 21:13:53 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGACTION_H
# define SIGACTION_H

# include "minishell.h"

/// @brief Signals hook
/// @param action t_sigaction
void		sa_hooks(void);

/// @brief Trigger action
/// @param action t_sigaction
/// @param handler action
/// @param signal sinal
void		signal_hook(t_sigaction *action, t_signal handler, int signal);

#endif