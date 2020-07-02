/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		pipe_condi(int i, t_pipe *p, int nb_cmd)
{
	if (i == 0)
		return (p->cmd && !ft_strcmp(p->cmd[0], "exit"));
	else if (i == 2)
		return (p->cmd && (nb_cmd > 1 || p->redird != NULL ||
		p->redirg != NULL));
	else
		return (p->cmd && nb_cmd == 1 && p->redird == NULL &&
		p->redirg == NULL);
}

void	start_pipe(int *flag, int *j, int nb_cmd, int *pipes)
{
	*flag = 0;
	*j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
}
