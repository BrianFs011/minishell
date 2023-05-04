/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:08:22 by briferre          #+#    #+#             */
/*   Updated: 2023/05/03 14:31:19 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "terminal.h"

int			bt_exit(t_ml *tml);

/// @brief Modify environment PWD
/// @param tml Struct t_ml from terminal.h
/// @return exit status
int			bt_cd(t_ml *tml);

/// @brief Write on terminal
/// @param splt t_string * with splt[0] = echo, splt[1]...[n] text
/// @return exit status
int			bt_echo(t_ml *tml);

/// @brief Find by environment PWD and print
/// @param tml struct tml
/// @return exit status
int			bt_pwd(t_ml *tml);

/// @brief Print all environment
/// @param tml struct t_tml *
/// @return exit status
int			bt_env(t_ml *tml);

/// @brief Sets local variables as environment and creates new environment
/// @param tml struct t_ml
/// @return exit staus
int			bt_export(t_ml *tml);

/// @brief Delete local and environment variables
/// @param start struct varlist with start node
/// @param string t_string with name from variable
/// @return exit status
int			bt_unset(t_varlist **start, t_string string);

/// @brief Remove one node from linked list
/// @param start struct varlist with start node
/// @param temp struct varlist with node to be removed
/// @param before struct varlist with node before temp
void		remove_no(t_varlist **start, t_varlist **temp, t_varlist **before);

/// @brief Find by local variable and difine as environment
/// @param tml struct t_ml
/// @return exit status
int			export_from_local_vars(t_ml *tml);

int			bt_print_export(t_varlist *start);

#endif