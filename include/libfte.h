/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfte.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:19:01 by briferre          #+#    #+#             */
/*   Updated: 2023/04/05 08:48:12 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTE_H
# define LIBFTE_H

# include "minishell.h"
# include "ft_string.h"

/// @brief Free pointer
/// @param ptr Addrs from pointer
void		ft_free(void *ptr);

/// @brief Join perror and exit
/// @param message Message error
/// @param type Type exit
void		ft_error(char *message, int type);

/// @brief Count the quantity of character
/// @param text t_string with text
/// @param character char with character for find into text
/// @return Quantity of character finded
int			ft_cc(t_string text, char character);

int			ft_strisalpha(t_string str);

#endif