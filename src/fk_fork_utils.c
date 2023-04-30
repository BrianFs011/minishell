/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:06 by briferre          #+#    #+#             */
/*   Updated: 2023/04/30 13:15:02 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct s_teste
{

}t_teste;

void	fk_call_new_process(t_ml *tml)
{
	int			fd;
	pid_t		pid;
	t_varlist	var;

	fd = -10;
	pid = fork();
	if (pid == -1)
		perror("Erro ao criar o processo filho\n");
	else if (pid != 0)
	{
		g_pid = pid;
		var.name = ft_strcpy("pid", FALSE);
		var.value = ft_strcpy(ft_itoa(pid), TRUE);
		// if (!ft_strcmp())

		vr_insert(&tml->pid_list, var, TRUE, TRUE);
		if (fd != -10)
			close(fd);
		if (tml->pp_quant != 0 && !(tml->i == tml->pp_quant))
			close(tml->pp_lpipes[tml->i][1]);
		// tml->exit_status = 0;
		// g_pid = G_FATHER;
	}
	else
	{
		g_pid = G_CHILD;
		tml->exit_status = tml_exec_child(tml, &fd);
	}
}

void	fk_wait_execs(t_ml *tml)
{
	int			new_exit_code;
	pid_t		pid;
	// pid_t		before_pid;
	t_varlist	*temp;
	// int	i;

	// // printf("processo 1: %s\nprocesso 2: %s\nprocesso 3: %p", temp->value, temp->next->value, temp->next->next);
	// temp = tml->pid_list;
	// i = 0;
	// while(temp && i < 10)
	// {
	// 	pid = ft_atoi(temp->value);
	// 	waitpid(pid, &new_exit_code, WNOHANG);
	// 	printf("%d %d %d\n", pid, new_exit_code, kill(pid, 0));
	// 	temp = temp->next;
	// 	if (temp == NULL)
	// 	{
	// 		temp = tml->pid_list;
	// 		i++;
	// 	}
	// }
	// printf("\nSaiu\n");
	// waitpid(pid, &new_exit_code, 0);
	// printf("processo 1: %d\nprocesso 2: %s\nprocesso 3: %p", kill(ft_atoi(temp->next->value), 0), temp->next->value, temp->next->next);


	// printf("\n%d %d\n", kill(ft_atoi(temp->value), 0), kill(ft_atoi(temp->next->value), 0));
	// if (kill(ft_atoi(temp->value), 0) != -1 && kill(ft_atoi(temp->next->value), 0) == -1)
	// {
	// 	kill(ft_atoi(temp->value), SIGTERM);
	// 	ft_print_error(NULL, "Broken pipe", FALSE);
	// }


	// pid = ft_atoi(temp->value);
	// waitpid(pid, &new_exit_code, 0);
	// printf("\n%d %d\n", pid, new_exit_code);

	// pid = -1;
	// temp = tml->pid_list;
	// while (temp)
	// {
	// 	if (!ft_strcmp(temp->name, "pid"))
	// 	{
	// 		before_pid = pid;
	// 		pid = ft_atoi(temp->value);
	// 		// printf("out: %d %d %d\n", before_pid, pid, kill(pid, 0));
	// 		waitpid(pid, &new_exit_code, WNOHANG);
	// 		// printf("%d %d %d\n", before_pid, pid, kill(pid, 0));
	// 		if (kill(pid, 0) == -1)
	// 		{
	// 			kill(before_pid, SIGTERM);
	// 		}
	// 	}
	// 	temp = temp->next;
	// }

	temp = tml->pid_list;
	while (temp)
	{
		if (!ft_strcmp(temp->name, "pid"))
		{
			pid = ft_atoi(temp->value);
			waitpid(pid, &new_exit_code, 0);
			new_exit_code = WEXITSTATUS(new_exit_code);
		}
		else
			new_exit_code = ft_atoi(temp->value);
		// pp_error(tml, &status);
		temp = temp->next;
	}
	// vr_print(tml->pid_list);
	vr_delete(&tml->pid_list);
	tml->pid_list = NULL;
	tml_exit_status(&tml->local_vars, new_exit_code, FALSE);
	tml->exit_status = new_exit_code;
}
