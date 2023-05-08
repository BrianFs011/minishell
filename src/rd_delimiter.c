/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:29:01 by briferre          #+#    #+#             */
/*   Updated: 2023/05/08 17:37:03 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_ctrl_c(int value, int set)
{
	static int	x;

	if (set)
		x = value;
	return (x);
}

static void	is_ctrl_d(t_ml *tml, t_string hd_eof, int *condition)
{
	t_string	error;

	*condition = 0;
	error = ft_strcat("here-document",
			" delimited by end-of-file (wanted `", FALSE, FALSE);
	error = ft_strcat(error, hd_eof, TRUE, FALSE);
	error = ft_strcat(error, "')", TRUE, FALSE);
	ft_print_error(NULL, error, FALSE);
	free(error);
	tml_exit_status(&tml->local_vars, 130, FALSE);
}

static void	is_input(t_ml *tml, t_string *temp, t_string *temp2)
{
	*temp = vr_descompress(tml, *temp);
	if (*temp2)
		*temp2 = ft_strcat(*temp2, *temp, TRUE, FALSE);
	else
		*temp2 = ft_strcpy(*temp, FALSE);
	*temp2 = ft_strcat(*temp2, "\n", TRUE, FALSE);
}

static void	handle(int sig)
{
	(void)sig;
	is_ctrl_c(130, 1);
}

t_string	rd_in_delimiter(t_ml *tml, t_string hd_eof)
{
	t_string	temp;
	t_string	temp2;
	int			condition;

	temp2 = NULL;
	temp = NULL;
	condition = 1;
	signal(SIGINT, handle);
	rl_getc_function = getc;
	while (condition)
	{
		temp = readline("> ");
		if (temp && ft_strcmp(temp, hd_eof))
			is_input(tml, &temp, &temp2);
		else if (!temp && is_ctrl_c(0, 0) == 0)
			is_ctrl_d(tml, hd_eof, &condition);
		else
			condition = 0;
		free (temp);
	}
	rl_getc_function = rl_getc;
	if (!temp2)
		temp2 = ft_strcpy("", FALSE);
	return (temp2);
}
