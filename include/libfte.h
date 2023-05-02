/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfte.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:19:01 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 17:55:29 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTE_H
# define LIBFTE_H

# include "minishell.h"
# include "ft_string.h"

long long int	ft_atoi_llint(const char *str);

/// @brief Free pointer
/// @param ptr Addrs from pointer
void			ft_free(void *ptr);

/// @brief Count the quantity of character
/// @param text t_string with text
/// @param character char with character for find into text
/// @return Quantity of character finded
int				ft_cc(t_string text, char character);

t_bool			ft_strisalpha(t_string str);

int				ft_isdigit_plus(int a);

t_string		ft_strcatc(t_string src1, char src2, t_bool free1);

#endif