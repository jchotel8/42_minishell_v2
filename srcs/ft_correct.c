#include "../includes/minishell.h"

char    *ft_findvarenv(char *str, t_list *lst)
{
    char **split;

    split = ft_split(str, '$');
    while (lst && lst->next)
    {
        if (!ft_strncmp(ft_strjoin(split[0], "="), lst->content, ft_strlen(ft_strjoin(split[0], "="))))
            return (lst->content);
        lst = lst->next;
    }
    return (NULL);
}

int     ft_isquote(char *str, char caract)
{
    size_t i;
    size_t s;

    i = 0;
    s = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\\')
            if (s == 0)
                s = 1;
            else
                s = 2;
        else if (str[i] == caract)
            if (s == 1)
                return (1);
            else
                return (0);
        i++;
    }
    return (0);
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

char    *ft_cleancmd(char **str, t_list *env)
{
    size_t  i;
    char    *new;

    i = 0;
    new = NULL;
    while (str[i])
    {
        if (ft_containvarenv(str[i]))
            if (ft_findvarenv(str[i], env) != NULL)
                new = ft_strjoin(new, ft_strndup(ft_findvarenv(str[i], env)));
            else
                new = NULL;
        else
            new = ft_strjoin(new, str[i]);
        i++;
    }
    free(str);
    return (new);
}