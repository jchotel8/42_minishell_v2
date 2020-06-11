#include "../includes/header.h"

void  ft_putchar(char caract)
{
	write(1, &caract, 1);
}

void  ft_putstr(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

void  ft_putnbr(int n)
{
	long int val;

	val = n;
	if (val < 0)
	{
		ft_putchar('-');
		val = -val;
	}
	if (val > 9)
	{
		ft_putnbr(val / 10);
		ft_putchar((val % 10) + '0');
	}
	else
		ft_putchar(val + '0');
}

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
void  do_dup(int j, int nb_cmd, int *pipes, char *redird, char *redirg, int typeredir)
{
	int fd;

	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	if (j < nb_cmd - 1 || redird != NULL)
	{
		if (typeredir == 1 && redird != NULL)
      		pipes[j * 2 + 1] = open(redird, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0644);
      	else if (typeredir == 2 && redird != NULL)
      		pipes[j * 2 + 1] = open(redird, O_WRONLY | O_CREAT | O_APPEND | O_RDONLY, 0644);
		dup2(pipes[j * 2 + 1], 1);
	}
	if (redirg != NULL)
	  	dup2(open(redirg, O_RDONLY), 0);
}


//V2 - N CMDS
void  do_pipe(char ***all, char **redird, char **redirg, int nb_cmd, int *ret)
{
	pid_t *pid;
	int   pipes[nb_cmd * 2 - 2];
	int   j;

  j = -1;
	if (!(pid = (pid_t *)malloc(sizeof(int) * nb_cmd + 1)))
		return ;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (j++ < nb_cmd - 1)
	{
		if (!(pid[j] = fork()))
		{
			do_dup(j, nb_cmd, pipes, redird[j], redirg[j], 1);
			close_pipes(nb_cmd * 2 - 2, pipes);
			if(execvp(*all[j], all[j]))
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

	char *cmd1[] = {"cat", "main.c", NULL};
	char *cmd2[] = {"grep", "p", NULL};
	char *cmd3[] = {"cut", "-b", "1-10", NULL};
	char *cmd4[] = {"head", "-n", "3", NULL};

	// char **cmd[] = {cmd1, cmd2, cmd3, cmd4};
	// char *redird[] = {NULL, "out1", "out2", NULL};
	// char *redirg[] = {NULL, NULL, NULL, NULL};
	// do_pipe(cmd, redird, redirg, 4, &rep);
	// printf("REP %d\n", rep);

	char **cmd_[] = {cmd2};    //grep p < main.c
	char *redird1[] = {"out3"};
	char *redirg1[] = {"main.c"};
	do_pipe(cmd_, redird1, redirg1, 1, &rep);
	printf("REP %d\n", rep);
}
