/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:08:22 by briferre          #+#    #+#             */
/*   Updated: 2023/04/07 12:09:02 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "terminal.h"

// ----- call builtins -----
int			bt_call_cd(t_ml *tml);

int			bt_call_echo(t_string *splt);

// ----- builtins -----
int			bt_exit(t_ml *tml);

/// @brief Modify path in terminal
/// @param tml Struct t_ml
int			bt_cd(t_ml *tml);

int			bt_echo(t_string *splt);

int			bt_pwd(t_ml *tml);

int			bt_env(t_varlist *start);

int			bt_export(t_ml *tml);

t_bool		bt_unset(t_varlist **start, t_string string);

#endif