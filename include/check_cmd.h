/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:17:52 by briferre          #+#    #+#             */
/*   Updated: 2023/04/08 09:00:00 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_CMD_H
# define CHECK_CMD_H

# include "terminal.h"

// command check coming from user
void		ck_check(t_ml *tml);

// turns text enclosed in quotes into a variable
void		ck_quotes(t_ml *tml);

// check for redirect commands
void		ck_redictions(t_ml *tml);

#endif