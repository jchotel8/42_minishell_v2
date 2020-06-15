#include "../includes/minishell.h"

int     ft_echo(char **cmd)
{
    size_t i;

    if (cmd[1] == "-n") 
    {
        i = 2;
        while (cmd[i])
            ft_putstr(cmd[i++]);
        return (1);
    }
    i = 1;
    while (cmd[i])
        ft_putstr(cmd[i++]);
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

void    ft_cd(char *dir)
{  
    return ;
}