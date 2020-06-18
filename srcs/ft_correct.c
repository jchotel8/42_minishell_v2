#include "../includes/minishell.h"

char *ft_findvarenv(char *str, t_list *lst)
{
    while (lst && lst->next)
    {
        if (!ft_strncmp(ft_strjoin(str, "="), lst->content, ft_strlen(ft_strjoin(str, "="))))
            return (lst->content);
        lst = lst->next;
    }
}