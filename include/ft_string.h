/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:29:41 by briferre          #+#    #+#             */
/*   Updated: 2023/03/22 15:58:03 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include "minishell.h"

/// @brief Get positions
/// @param string t_string
/// @param c char
/// @return a vector with the positions that char c appear
int			*ft_strvchr(t_string string, char c);

/// @brief Compare two strings
/// @param str1 String 1
/// @param str2 String 2
/// @return If equal if 0
int			ft_strcmp(t_string str1, t_string str2);

/// @brief Copy src to dest not use "text" use ft_strcpy("text")
/// @param src What wanna copy
/// @param src_free Is free src?
/// @return Dest
t_string	ft_strcpy(t_string src, t_bool src_free);

/// @brief Concat src1 and src2
/// @param src1 String 1
/// @param src2 String 2
/// @param free1 Is free memory string 1
/// @param free2 Is free memory string 2
/// @return New String with string 1 + string 2
t_string	ft_strcat(t_string src1, t_string src2, t_bool free1, t_bool free2);

/// @brief Replace a string
/// @param dest t_string
/// @param src t_string
/// @param free1 t_bool
/// @param free2 t_bool
/// @return return t_string src
t_string	ft_strrpc(t_string dest, t_string src, t_bool free1, t_bool free2);

#endif
