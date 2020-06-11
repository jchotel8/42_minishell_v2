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

	i = 0;
	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
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
	i = 0;
	while (redirg[i] != NULL)
	  	dup2(open(redirg[i++], O_RDONLY), 0);
}


//V2 - N CMDS
void  do_pipe(char **cmd, char ***redird, char ***redirg, int nb_cmd, int *ret)
{
	pid_t *pid;
	int   pipes[nb_cmd * 2 - 2];
	int   j;
	char **all;

  j = -1;
	if (!(pid = (pid_t *)malloc(sizeof(int) * nb_cmd + 1)))
		return ;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (j++ < nb_cmd - 1)
	{
		if (!(pid[j] = fork()))
		{
			all = ft_split(cmd[j], ' ');
			do_dup(j, nb_cmd, pipes, redird[j], redirg[j], 2);
			close_pipes(nb_cmd * 2 - 2, pipes);
			if(execvp(*all, all))
				exit(-1);
		}
	}
	close_pipes(nb_cmd * 2 - 2, pipes);
	wait_pipes(nb_cmd, pid, ret);
	free(pid);
}

int   main(int ac, char **av)
{
	int     rep;

	char *cmd1 = "grep p";
	char *cmd2 = "cut -b 1-10";
	char *cmd3 = "cut -b 2-5";
	char *cmd4 = "head -n 3";

	char *redird1[] = {NULL};
	char *redird2[] = {NULL};
	char *redird3[] = {NULL};
	char *redird4[] = {"out1", "out2", "out4", NULL};

	char *redirg1[] = {"srcs/ft_pipes.c", NULL};
	char *redirg2[] = {NULL};
	char *redirg3[] = {NULL};
	char *redirg4[] = {NULL};

	char *cmd[] = {cmd1, cmd2, cmd3, cmd4};
	char **redird[] = {redird1, redird2, redird3, redird4};
	char **redirg[] = {redirg1, redirg2, redirg3, redirg4};
	do_pipe(cmd, redird, redirg, 4, &rep);
	printf("REP %d\n", rep);

	// char **cmd_[] = {cmd2};    //grep p < main.c
	// char *redird1[] = {"out3"};
	// char *redirg1[] = {"main.c"};
	// do_pipe(cmd_, redird1, redirg1, 1, &rep);
	// printf("REP %d\n", rep);
}
