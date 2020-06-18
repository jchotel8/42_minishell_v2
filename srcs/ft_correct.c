#include "../includes/minishell.h"

char    *ft_findvarenv(char *str, t_list *lst)
{
    while (lst && lst->next)
    {
        if (!ft_strncmp(ft_strjoin(str, "="), lst->content, ft_strlen(ft_strjoin(str, "="))))
            return (lst->content);
        lst = lst->next;
    }
}

int     ft_containvarenv(char *str)
{
    size_t  i;
    char    b;

    i = 0;
    while (str[i])
    {
        if (b == '$' && !ft_isspace(str[i]))
            return (1);
        b = str[i];
        i++;
    }
    return (0);
}