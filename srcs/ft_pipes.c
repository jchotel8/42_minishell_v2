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

//V2 - functions
void  do_dup(int j, int nb_cmd, int *pipes, char **redird, char **redirg, int typeredir)
{
	size_t i;
	int fd;

	i = 0;
	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	while (redirg[i] != NULL)
	{
		if ((fd = open(redirg[i++], O_RDONLY)) < 0)
			return ;
		dup2(fd, 0);
	}
	i = 0;	  
	if (j < nb_cmd - 1 || redird[i] != NULL)
	{
		while (redird[i])
		{
			if (typeredir == 1 && redird[i] != NULL)
      			pipes[j * 2 + 1] = open(redird[i], O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0644);
      		else if (typeredir == 2 && redird[i] != NULL)
      			pipes[j * 2 + 1] = open(redird[i], O_WRONLY | O_CREAT | O_APPEND | O_RDONLY, 0644);
      		i++;
      	}
		dup2(pipes[j * 2 + 1], 1);
	}
}


//V2 - N CMDS
void  do_pipe(char **cmd, char ***redird, char ***redirg, int nb_cmd, int *ret)
{
	pid_t pid[nb_cmd];
	int   pipes[nb_cmd * 2 - 2];
	int   j;
	char **all;

  	j = -1;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (++j < nb_cmd)
	{
		if (!(pid[j] = fork()))
		{
			all = ft_split(cmd[j], ' ');
			do_dup(j, nb_cmd, pipes, redird[j], redirg[j], 1);
			close_pipes(nb_cmd * 2 - 2, pipes);
			if(execvp(*all, all))
				exit(-1);
		}
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, ret);
}
