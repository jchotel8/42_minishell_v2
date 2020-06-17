#include "../includes/minishell.h"

void    ft_putnstr(char *str, size_t start)
{
    size_t i;

    i = 0;
    while (str[i++])
        if (i >= start)
        ft_putchar(str[i]);
}

void    ft_printlstif(char **str, t_list *lst)
{
    size_t i;

    i = 1;
    while (lst && lst->next)
    {
        if (!ft_strncmp(ft_strjoin(str[0], "="), lst->content, ft_strlen(ft_strjoin(str[0], "="))))
        {
            ft_putnstr(lst->content, ft_strlen(ft_strjoin(str[0], "=")));
            return ;
        }
        lst = lst->next;
    }
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
            if (cmd[i][0] == '$')
                ft_printlstif(ft_split(cmd[i], '$'), lst);
            else
                ft_putstr(cmd[i]);
            i++;
        }
        return (1);
    }
    i = 1;
    while (cmd[i]) {
        if (i >= 2)
            ft_putchar(' ');
        if (cmd[i][0] == '$')
            ft_printlstif(ft_split(cmd[i], '$'), lst);
        else
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