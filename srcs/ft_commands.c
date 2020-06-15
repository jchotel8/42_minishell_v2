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

int     do_exec(char **cmd)
{
    if (!ft_strcmp(cmd[0], "echo"))
    {
        ft_echo(cmd);
        return (0);
    }
    else if (!ft_strcmp(cmd[0], "pwd"))
    {
        ft_pwd();
        return (0);
    }
    else if (execvp(cmd[0], cmd))
        return (1);
    return (0);
}