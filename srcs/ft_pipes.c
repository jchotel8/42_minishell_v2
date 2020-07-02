/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir_in(t_pipe *p)
{
	int		fd;
	t_list	*tmp;

	tmp = p->redirg;
	while (tmp)
	{
		if ((fd = open(tmp->content, O_RDONLY)) < 0)
			return ;
		dup2(fd, 0);
		tmp = tmp->next;
	}
}

void	do_redir_out(t_pipe *p, int *pipes, int j)
{
	t_list	*tmp;
	t_list	*tmpt;

	tmpt = p->typed;
	tmp = p->redird;
	while (tmp)
	{
		if (!ft_strcmp(tmpt->content, "1"))
			pipes[j * 2 + 1] = open(tmp->content, O_WRONLY |
			O_CREAT | O_TRUNC | O_RDONLY, 0644);
		else if (!ft_strcmp(tmpt->content, "2"))
			pipes[j * 2 + 1] = open(tmp->content, O_WRONLY |
			O_CREAT | O_APPEND | O_RDONLY, 0644);
		tmp = tmp->next;
		tmpt = tmpt->next;
	}
}

void	do_dup(int j, int nb_cmd, int *pipes, t_pipe *p)
{
	int		fd;
	t_list	*tmp;
	t_list	*tmpt;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	do_redir_in(p);
	if (j < nb_cmd - 1 || p->redird)
	{
		do_redir_out(p, pipes, j);
		dup2(pipes[j * 2 + 1], 1);
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
}

int		pipe_condition(int i, t_pipe *p, int nb_cmd)
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

void	do_pipe(t_list *line, int nb_cmd, t_list **env)
{
	pid_t	pid[nb_cmd];
	int		pipes[nb_cmd * 2 - 2];
	int		j;
	t_pipe	p;
	int		flag;

	flag = 0;
	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (++j < nb_cmd)
	{
		if ((rep = parse_redir(line->content, &p, *env)) == 0)
		{
			if (pipe_condition(0, &p, nb_cmd))
				flag = 1;
			else if (pipe_condition(2, &p, nb_cmd) && !(pid[j] = fork()))
			{
				do_dup(j, nb_cmd, pipes, &p);
				rep = ft_exec(p.cmd, env);
				rep <= 0 ? exit(0) : 0;
				rep == 8 ? exit(1) : 0;
				rep == 127 ? exit(3) : 0;
			}
			else if (pipe_condition(1, &p, nb_cmd))
				(rep = ft_exec2(p.cmd, env)) == 127 ? exit(3) : 0;
		}
		free_pipe(&p);
		line = line->next;
	}
	wait_pipes(nb_cmd, pid, &rep, pipes);
	flag == 1 ? exit(0) : 0;
}
