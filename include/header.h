/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:59:03 by briferre          #+#    #+#             */
/*   Updated: 2023/03/10 16:40:10 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <fcntl.h>

# include <curses.h>
# include <term.h>

# include <sys/wait.h>
# include <sys/resource.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

# include "libft.h"

# define PATH_MAX 4096
# define TRUE 1
# define FALSE 0
# define RUNNIG 1
# define EXIT 0
# define EXIT_SILENCED 2

typedef char				*t_string;
typedef int					t_bool;
typedef struct sigaction	t_sigaction;
typedef void				(*t_signal)(int);

typedef struct s_vars
{
	t_string		name;
	t_string		value;
	int				size;
	struct s_vars	*next;
}t_vars;

typedef struct s_ml
{
	t_string	user;
	t_string	host;
	t_string	path;
	t_string	signal;
	t_string	cmd;
	t_string	*pp_cmd;
	t_string	*sprt_cmd;
	t_string	temp;
	t_string	info;
	t_string	*env;
	t_string	*paths;
	t_sigaction	sa;
	t_vars		*vars;
	int			running;
	int			pp_quant;
	int			**pp_lpipes;
	int			fd_pipe[2];
	int			i;
	pid_t		pid_child;
}t_ml;

extern pid_t	g_pid;

/// @brief Free user, host and path from t_ml
/// @param tml	Struct t_ml
void		tml_free_uhp(t_ml *tml);

/// @brief Free a list from t_string
/// @param string_list List from t_string
void		tml_free_sprt_cmd(t_string *string_list);

/// @brief Create a new process
/// @param pid Pid from fork function
/// @param tml Struct t_ml
void		fk_call_new_process(pid_t pid, t_ml *tml);

/// @brief Get text from file text
/// @param path Path from file text
/// @return t_string with text
t_string	fl_get_text(t_string path);

/// @brief Free pointer
/// @param ptr Addrs from pointer
void		ft_free(void *ptr);

/// @brief Join perror and exit
/// @param message Message error
/// @param type Type exit
void		ft_error(char *message, int type);

/// @brief For now exit the loop
/// @param tml Struct t_ml
void		ft_exit(t_ml *tml);

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

/// @brief Compare two strings
/// @param str1 String 1
/// @param str2 String 2
/// @return If equal if 0
int			ft_strcmp(t_string str1, t_string str2);


t_string	ft_strrpc(t_string dest, t_string src, t_bool free1, t_bool free2);

/// @brief Count the quantity of character
/// @param text t_string with text
/// @param character char with character for find into text
/// @return Quantity of character finded
int			ft_cc(t_string text, char character);

/// @brief Modify path in terminal
/// @param tml Struct t_ml
void		tml_cd(t_ml *tml);

/// @brief Create a array of pipe[2]
/// @param tml struct t_ml
void		pp_linked_pipes(t_ml *tml);

/// @brief Delete array of pipe[2]
/// @param tml struct t_ml
void		pp_delete_linked_pipes(t_ml *tml);

/// @brief Switch STDIN_FILENO for pipe[0] and STDOUT_FILENO for pipe[1]
/// @param tml struct t_ml
void		pp_switch(t_ml *tml);

/// @brief Called when have one or more pipes
/// @param tml struct t_ml
void		pp_call_pipe(t_ml *tml);

/// @brief Create a file for out
/// @param tml struct t_ml
/// @param fd addrs file descriptor
void		rd_redirection(t_ml *tml, int *fd);

/// @brief Run program in terminal
/// @param tml Struct t_ml
void		tml_exec(t_ml *tml, int *fd);

/// @brief Get user, host and path from user
/// @param tml Struct t_ml
void		tml_get_uhp(t_ml *tml);

/// @brief Create line who is show in terminal
/// @param tml Struct t_ml
void		tml_create_uhp_line(t_ml *tml);

/// @brief Signals hook
/// @param action t_sigaction
void		sa_hooks(t_sigaction *action);

/// @brief Trigger action
/// @param action t_sigaction
/// @param handler action
/// @param signal sinal
void		signal_hook(t_sigaction *action, t_signal handler, int signal);

/// @brief Replace variable for value
/// @param tml struct t_ml
/// @param i '$' position
void		ft_replace(t_ml *tml, int *i);

/// @brief Check terminal input
/// @param tml struct t_ml
void		ck_check(t_ml *tml);

/// @brief Add variable in linked list
/// @param tml struct t_ml
// void		vr_add_variable(t_ml *tml);
void		vr_add_variable(t_vars **start, t_string variables);

/// @brief Insert in linked list
/// @param start Adress struct t_vars
/// @param var t_vars with content
void		vr_insert(t_vars **start, t_vars var);

/// @brief Print linked list
/// @param start Init from list
void		vr_print(t_vars *start);

/// @brief Clear memória from linked list
/// @param start Adress struct t_vars
void		vr_delete(t_vars **start);

/// @brief Find for variable in linked list
/// @param start struct t_vars
/// @param name t_string with variable
/// @return t_string with value from variable or empty string
t_string	vr_get_var(t_vars *start, t_string name);

#endif
