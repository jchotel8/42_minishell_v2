#include "../includes/minishell.h"

void  init_pipes(int nb_pipes, int *pipes)
{
	int i;

	i = 0;
	while ((2 * i) < nb_pipes)
		pipe(pipes + (2 * i++));
}

void  close_pipes(int nb_pipes, int *pipes)
{
	while (nb_pipes--)
		close(pipes[nb_pipes]);
}

void  wait_pipes(int nb_cmd, pid_t *pid, int *ret)
{
	int i;

	i = 0;
	while (i < nb_cmd)
		waitpid(pid[i++], ret, 0);
}

void  do_dup(int j, int nb_cmd, int *pipes, t_list *redird, t_list *redirg, int typeredir)
{
	int fd;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	while (redirg)
	{
		if ((fd = open(redirg->content, O_RDONLY)) < 0)
			return ;
		dup2(fd, 0);
		redirg = redirg->next;
	}  
	if (j < nb_cmd - 1 || redird)
	{
		while (redird)
		{
			if (typeredir == 1)
      			pipes[j * 2 + 1] = open(redird->content, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0644);
      		else if (typeredir == 2)
      			pipes[j * 2 + 1] = open(redird->content, O_WRONLY | O_CREAT | O_APPEND | O_RDONLY, 0644);
			redird = redird->next;
      	}
		dup2(pipes[j * 2 + 1], 1);
	}
}

void  do_pipe(t_list *line, int nb_cmd, int *ret, t_list **env)
{
	pid_t pid[nb_cmd];
	int   pipes[nb_cmd * 2 - 2];
	int   j;
	char **all;
	t_pipe pipe;

  	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (++j < nb_cmd)
	{
		if (nb_cmd != 1 && !(pid[j] = fork()))
		{
			parse_redir(line->content, &pipe);
			do_dup(j, nb_cmd, pipes, pipe.redird, pipe.redirg, 1);
			close_pipes(nb_cmd * 2 - 2, pipes);
			if (ft_exec(pipe.cmd, env) <= 0)
				exit(0);
		}
		// else
		// {
		// 	parse_redir(line->content, &pipe);
		// 	if (ft_exec(pipe.cmd, env) == -1)
		// 		exit(-1);
		// }
		line = line->next;
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, ret);
}
