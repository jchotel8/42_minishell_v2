#include "header.h"

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
void  do_dup(int j, int nb_cmd, int *pipes, char *redir, int typeredir)
{
	if (j > 0)
		dup2(pipes[j * 2 - 2], 0);
	if (j < nb_cmd - 1)
		dup2(pipes[j * 2 + 1], 1);
  if (redir != NULL && typeredir > 0)
  {
    if (typeredir == 1)
      pipes[j * 2 + 1] = open(redir, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY,0644);
    else if (typeredir == 2)
      pipes[j * 2 + 1] = open(redir, O_WRONLY | O_CREAT | O_APPEND | O_RDONLY,0644);
  	dup2(pipes[j * 2 + 1], 1);
  }
}


//V2 - N CMDS
void  do_pipe(char ***all, char **redir,int nb_cmd, int *ret)
{
	pid_t *pid;
	int   pipes[nb_cmd * 2 - 2];
	int   j;

  j = -1;
	if (!(pid = (pid_t *)malloc(sizeof(int) * nb_cmd + 1)))
		return ;
	init_pipes(nb_cmd * 2 - 2, pipes);
	while (j++ < nb_cmd)
	{
		if (!(pid[j] = fork()))
		{
			do_dup( j, nb_cmd, pipes, redir[j], 2);
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

	char *cat_args[] = {"cat", "main.c", NULL};
	char *grep_args[] = {"grep", "p", NULL};
	char *cut_args[] = {"cut", "-b", "1-10", NULL};
	char *cut_args1[] = {"head", "-n", "3", NULL};
	char **stock[] = {cat_args, grep_args, cut_args, cut_args1};

  char *cat_args2[] = {"out", NULL};
	char *grep_args2[] = {NULL};
	char *cut_args2[] = {"out2", NULL};
	char *cut_args3[] = {NULL};
	char *redir[] = {"out", NULL, "out2", NULL};

  do_pipe(stock, redir, 4, &rep);
	printf("REP %d\n", rep);
}
