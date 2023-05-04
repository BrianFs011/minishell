/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:59:03 by briferre          #+#    #+#             */
/*   Updated: 2023/05/04 18:05:07 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <fcntl.h>

# include <curses.h>
# include <term.h>

# include <sys/wait.h>
# include <sys/resource.h>
# include <errno.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

# include <sys/stat.h>

# include "libft.h"

# define TRUE 1
# define FALSE 0
# define RUNNIG 1
# define EXIT 0
# define EXIT_SILENCED -1
# define G_FATHER 0
# define G_CHILD  1
# define G_QUOTE  2
# define G_EXIT  -1

# define PINK "\001\033[1;35m\002"
# define GREY "\001\033[22;39m\002"
# define WHITE "\001\033[1;90m\002"
# define RESET "\001\033[0m\002"

typedef char				*t_string;
typedef int					t_bool;
typedef struct sigaction	t_sigaction;
typedef void				(*t_signal)(int);

extern pid_t				g_pid;

#endif
