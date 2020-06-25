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

void	do_dup(int j, int nb_cmd, int *pipes, t_pipe *p, int typeredir)
{
	int	fd;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	while (p->redirg)
	{
		if ((fd = open(p->redirg->content, O_RDONLY)) < 0)
			return ;
		dup2(fd, 0);
		p->redirg = p->redirg->next;
	}  
	if (j < nb_cmd - 1 || p->redird)
	{
		while (p->redird)
		{
			if (typeredir == 1)
				pipes[j * 2 + 1] = open(p->redird->content, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0644);
			else if (typeredir == 2)
				pipes[j * 2 + 1] = open(p->redird->content, O_WRONLY | O_CREAT | O_APPEND | O_RDONLY, 0644);
			p->redird = p->redird->next;
		}
		dup2(pipes[j * 2 + 1], 1);
	}
}

void	do_pipe(t_list *line, int nb_cmd, int *ret, t_list **env)
{
	pid_t	pid[nb_cmd];
	int		pipes[nb_cmd * 2 - 2];
	int		j;
	char	**all;
	t_pipe	pipe;
	int		att;

	att = 0;
	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (++j < nb_cmd)
	{
		parse_redir(line->content, &pipe, *env);
		if (pipe.cmd[0] && !ft_strcmp(pipe.cmd[0], "exit"))
			att = 1;
		else if ((nb_cmd != 1 || pipe.redird != NULL) && !(pid[j] = fork()))
		{
			do_dup(j, nb_cmd, pipes, &pipe, 1);
			close_pipes(nb_cmd * 2 - 2, pipes);
			if ((*ret = ft_exec(pipe.cmd, env)) <= 0) //renvoi 0 ou 8 si un des bins (S/F) sinon : NA if success, -1 if fail, 127 if not found, 1 if ?
				exit(0); //il faut exit seulement dans le cas ou execve fail et si une de mes commandes fails
			if (*ret == 8)
				exit(1);
			if (*ret == 127)
				exit(3);
		}
		else if (nb_cmd == 1 && pipe.redird == NULL)
		{
			if (pipe.cmd[0])
				if ((*ret = ft_exec2(pipe.cmd, env)) != 0 && *ret != 8)
					exit(0);
		}
		line = line->next;
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, ret);
	if (att == 1)
		ft_exit(pipe.cmd, *env);
}
