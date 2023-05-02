/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:44:59 by briferre          #+#    #+#             */
/*   Updated: 2023/05/02 17:56:06 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_varlist
{
	t_string			name;
	t_string			value;
	int					size;
	struct s_varlist	*next;
}t_varlist;

/// @brief Add variable in linked list
/// @param tml struct t_ml
// void		vr_add_variable(t_ml *tml);
t_varlist	vr_get_name_value(t_string variables);

/// @brief Insert in linked list
/// @param start Adress struct t_varlist
/// @param var t_varlist with content
void		vr_insert(t_varlist **start, t_varlist var,
				t_bool free_name, t_bool free_value);

/// @brief Update value in linked list
/// @param start Adress struct t_varlist
/// @param var t_varlist with content
void		vr_update_insert(t_varlist **start, t_varlist var);

/// @brief Print linked list
/// @param start Init from list
void		vr_print(t_varlist *start);

/// @brief Clear memória from linked list
/// @param start Adress struct t_varlist
void		vr_delete(t_varlist **start);

/// @brief Find for variable in linked list
/// @param start struct t_varlist
/// @param name t_string with variable
/// @return t_string with value from variable or empty string or name
t_string	vr_get_value(t_varlist *start, t_string name, t_bool empty);

t_string	get_env(t_varlist *start, t_string string, int *i);

t_bool		vr_change_value(t_varlist **start, t_varlist var);

t_bool		vr_delete_node(t_varlist **start, t_varlist var);

#endif