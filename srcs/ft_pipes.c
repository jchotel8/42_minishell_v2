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

void	wait_pipes(int nb_cmd, pid_t *pid, int *ret)
{
	int i;

	i = 0;
	while (i < nb_cmd)
		waitpid(pid[i++], ret, 0);
}

void	do_dup(int j, int nb_cmd, int *pipes, t_pipe *p)
{
	int	fd;
	t_list *tmp;
	t_list *tmpt;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	tmp = p->redirg;
	while (tmp)
	{
		if ((fd = open(tmp->content, O_RDONLY)) < 0)
			return ;
		dup2(fd, 0);
		tmp = tmp->next;
	}
	tmpt = p->typed;
	if (j < nb_cmd - 1 || p->redird)
	{
		tmp = p->redird;
		while (tmp)
		{
			if (!ft_strcmp(tmpt->content, "1"))
				pipes[j * 2 + 1] = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0644);
			else if (!ft_strcmp(tmpt->content, "2"))
				pipes[j * 2 + 1] = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND | O_RDONLY, 0644);
			tmp = tmp->next;
			tmpt = tmpt->next;
		}
		dup2(pipes[j * 2 + 1], 1);
	}
}

void	free_pipe(t_pipe *p)
{
	ft_freearray(p->cmd);
	ft_lstclear(&p->redirg, *free);
	ft_lstclear(&p->redird, *free);
	ft_lstclear(&p->typeg, *free);
	ft_lstclear(&p->typed, *free);
}

void	do_pipe(t_list *line, int nb_cmd, int *ret, t_list **env)
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
		if (parse_redir(line->content, &p, *env))
			*ret = 1;
		else
		{
			if (p.cmd[0] && !ft_strcmp(p.cmd[0], "exit"))
				flag = 1;
			else if ((nb_cmd != 1 || p.redird != NULL || p.redirg != NULL) && !(pid[j] = fork()))
			{
				do_dup(j, nb_cmd, pipes, &p);
				close_pipes(nb_cmd * 2 - 2, pipes);
				*ret = ft_exec(p.cmd, env);
				free_pipe(&p);
				if (*ret <= 0) //renvoi 0 ou 8 si un des bins (S/F) sinon : NA if success, -1 if fail, 127 if not found, 1 if ?
					exit(0); //il faut exit seulement dans le cas ou execve fail et si une de mes commandes fails
				if (*ret == 8)
					exit(1);
				if (*ret == 127)
					exit(3);
			}
			else if (nb_cmd == 1 && p.redird == NULL && p.redirg == NULL)
			{
				if (p.cmd[0])
					if ((*ret = ft_exec2(p.cmd, env)) != 0 && *ret != 8)
						exit(0);
			}
		}
		free_pipe(&p);
	 	line = line->next;
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, ret);
	if (flag == 1)
		ft_exit(p.cmd, *env);
}
