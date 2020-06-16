#include "../includes/minishell.h"

int     ft_echo(char **cmd)
{
    size_t i;

    if (cmd[1] == NULL)
    {
        ft_putchar('\n');
        return (1);
    }
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
    return (0);
}

int    ft_pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
    {
        miniprintf("%s\n", cwd);
        return (0);
    }
    ft_putstr("Failed to get pwd");
    return (1);
}

char *get_wd()
{
    char    cwd[1024];
    char	**files;
    int     i;

    i = 0;
    if (getcwd(cwd, sizeof(cwd)))
    {
        files = ft_split(cwd, '/');
        while (files && files[i])
		    i++;
        return (ft_strdup(files[i - 1]));
    }
    else
        return(ft_strdup("no WD"));
}