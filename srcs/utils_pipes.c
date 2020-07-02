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

void	init_pipes(int nb_pipes, int *pipes)
{
	int i;

	i = 0;
	while ((2 * i) < nb_pipes)
		pipe(pipes + (2 * i++));
}

void	close_pipes(int nb_pipes, int *pipes)
{
	while (nb_pipes--)
		close(pipes[nb_pipes]);
}

void	wait_pipes(int nb_cmd, pid_t *pid, int *ret, int *pipes)
{
	int i;

	i = 0;
	close_pipes(nb_cmd * 2 - 2, pipes);
	while (i < nb_cmd)
		waitpid(pid[i++], ret, 0);
}

void	free_pipe(t_pipe *p)
{
	ft_freearray(p->cmd);
	ft_lstclear(&p->redirg, *free);
	ft_lstclear(&p->redird, *free);
	ft_lstclear(&p->typeg, *free);
	ft_lstclear(&p->typed, *free);
}

void	set_pipe(t_pipe *p)
{
	p->cmd = NULL;
	p->redird = NULL;
	p->redirg = NULL;
	p->typed = NULL;
	p->typeg = NULL;
}
