/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briferre <briferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:41:58 by briferre          #+#    #+#             */
/*   Updated: 2023/03/07 17:02:23 by briferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	temp01(t_ml *tml, t_string temp[], int *i)
{
	temp[0] = malloc(sizeof(char) * (*i) + 1);
	ft_strlcpy(temp[0], tml->cmd, (size_t)((*i) + 1));
}

static void	temp02(t_ml *tml, t_string temp[], int *i, int *j)
{
	int	cont;
	int	k;

	cont = 0;
	while (tml->cmd[++(*j)] && tml->cmd[(*j)] != ' ' && tml->cmd[(*j)] != '$')
		cont++;
	temp[1] = malloc(sizeof(char) * cont + 1);
	(*j) = (*i);
	k = -1;
	while (tml->cmd[++(*j)] && tml->cmd[(*j)] != ' ' && tml->cmd[(*j)] != '$')
		temp[1][++k] = tml->cmd[(*j)];
	temp[1][++k] = '\0';
}

static void	temp03(t_ml *tml, t_string temp[], int *j)
{
	int	k;
	int	cont;

	cont = 0;
	(*j)--;
	while (tml->cmd[++(*j)])
		cont++;
	temp[2] = malloc(sizeof(char) * cont + 2);
	(*j) -= cont + 1;
	k = -1;
	while (tml->cmd[++(*j)])
		temp[2][++k] = tml->cmd[(*j)];
	temp[2][++k] = '\0';
}

void	ft_replace(t_ml *tml, int *i)
{
	t_string	temp[4];
	int			j;

	j = (*i);
	// printf("%c %d\n", tml->cmd[j], tml->cmd[j + 1]);
	temp01(tml, temp, i);
	temp02(tml, temp, i, &j);
	temp03(tml, temp, &j);
	free(tml->cmd);
	tml->cmd = ft_strcpy(temp[0], TRUE);
	temp[3] = vr_get_var(tml->vars, temp[1]);
	if (!ft_strcmp(temp[3], ""))
		(*i) -= ft_strlen(temp[1]);
	tml->cmd = ft_strcat(tml->cmd, temp[3], TRUE, TRUE);
	free(temp[1]);
	tml->cmd = ft_strcat(tml->cmd, temp[2], TRUE, TRUE);
}
