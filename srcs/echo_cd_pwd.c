#include "../includes/minishell.h"

void    ft_putnstr(char *str, size_t start)
{
    size_t i;

    i = 0;
    while (str[i++])
        if (i >= start)
        ft_putchar(str[i]);
}

size_t  ft_strlenif(char *str, char c)
{
    size_t  i;
    size_t  j;
    size_t  s;

    i = 0;
    j = 0;
    s = 0;
    while (str[i])
    {
        if (str[i++] == c)
            s = 1;
        else if (s == 1)
            j++;
        i++;
    }
    return (j);
}

char    *ft_strndup(char *str)
{
    size_t  i;
    size_t  j;
    size_t  s;
    char    *tmp;

    i = 0;
    j = 0;
    s = 0;
    if (!(tmp = ft_calloc(sizeof(char), (ft_strlenif(str, '=') + 1))))
        return (NULL);
    while (str[i])
    {
        if (s == 1)
            tmp[j++] = str[i];
        else if (str[i] == '=')
            s = 1;
        i++;
    }
    free(str);
    return (tmp);
}

int     ft_echo(char **cmd, t_list *lst)
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
            ft_putstr(cmd[i]);
            i++;
        }
        return (1);
    }
    i = 1;
    while (cmd[i]) {
        if (i >= 2)
            ft_putchar(' ');
        ft_putstr(cmd[i]);
        i++;
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