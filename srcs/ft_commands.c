#include "../includes/minishell.h"

int     ft_echo(char **cmd)
{
    size_t i;

    if (!ft_strcmp(cmd[1], "-n")) 
    {
        i = 2;
        while (cmd[i]) {
            if (i >= 3)
                ft_putchar(' ');
            ft_putstr(cmd[i++]);
        }
        return (1);
    }
    i = 1;
    while (cmd[i]) {
        if (i >= 2)
            ft_putchar(' ');
        ft_putstr(cmd[i++]);
    }
    ft_putchar('\n');
    return (1);
}

int    ft_pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
    {
        ft_putstr(cwd);
        return (1);
    }
    return (0);
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