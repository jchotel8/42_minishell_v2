#include "header.h"

void    ft_putchar(char caract)
{
    write(1, &caract, 1);
}

void    ft_putstr(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        ft_putchar(str[i++]);
}

void    ft_putnbr(int n)
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

void    closepipes(int *pipes, int n)
{
    int     i;

    i = 0;
    while (i < n)
        close(pipes[i++]);
}

void    dodup(int *pipes, int n, int i)
{
    if (i != 0)
        dup2(pipes[(i * 2) - 2], 0);
    if (i != (n - 1))
        dup2(pipes[(i * 2) + 1], 1);

}

void    do_pipe(char ***cmds, int n, int *rep)
{
    int status;
    int i;
    int k;
    size_t j;
    pid_t *pids = malloc(sizeof(pid_t) * (n));
    int pipes[(n - 1) * 2];

    j = 0;
    k = 0;
     while (j < (n - 1))
        pipe(pipes + (2 * j++));
    while (k < n)
    {
        if ((pids[k] = fork()) == 0)
        {
        
            dodup(pipes, n, k);
            closepipes(pipes, ((n - 1) * 2));
            if (execvp(cmds[k][0], cmds[k]))
                exit(-1);
        }
        k++;
    }
   
    closepipes(pipes, ((n - 1) * 2));
    i = 0;
    while (i < n)
        waitpid(pids[i++], rep, 0);
}

/*int     main()
{
    int     rep;

    char *cat_args[] = {"cat", "main.c", NULL};
    char *grep_args[] = {"grep", "p", NULL};
    char *cut_args[] = {"cut", "-b", "1-10", NULL};
    char *cut_args2[] = {"head", "-n", "3", NULL};
    char **stock[] = {cat_args, grep_args, cut_args, cut_args2};

    dopipes(stock, 4, &rep);
    printf("REP %d\n", rep);
} */
