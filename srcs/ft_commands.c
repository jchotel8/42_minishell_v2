#include "../includes/minishell.h"

void    ft_echo(char **cmd)
{
    size_t i;

    i = 1;
    while (cmd[i])
        ft_putstr(cmd[i++]);
}

void    ft_pwd()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    ft_putstr(cwd);
}