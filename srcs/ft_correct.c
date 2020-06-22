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

int     ft_isinquote(char *str, char caract)
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
        if (b == '$' && !ft_isspace(str[i]) && !ft_isinquote(str, '$'))
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
    char    *tmp;

    i = 0;
    new = NULL;
    tmp = NULL;
    while (str[i])
    {
        tmp = NULL;
        if (ft_containvarenv(str[i]) && ft_findvarenv(str[i], env))
            tmp = ft_strndup(ft_findvarenv(str[i], env));
        else if (!ft_containvarenv(str[i]))
            tmp = str[i];
        if (tmp != NULL)
            new = ft_strjoin(new, tmp);
        i++;
    }
    if (!new)
        if (!(new = ft_calloc(1, sizeof(char))))
            return (NULL);
    free(str);
    return (new);
}