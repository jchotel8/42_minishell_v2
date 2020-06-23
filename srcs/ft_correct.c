#include "../includes/minishell.h"

char    *ft_findvarenv(char *str, t_list *lst)
{
    char **split;

    str = ft_strtrim_quote(str);
    split = ft_split(str, '$');
    while (lst && lst->next)
    {
        if (!ft_strlcmp(ft_strjoin(split[0], "="), lst->content))
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
    char    prev;
    //char    quote;

    i = 0;
    while (str[i])
    {
        if (prev == '$' && !ft_isspace(str[i]) && !ft_isinquote(str, '$'))
            return (1);
        prev = str[i++];
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
    free(str);
    return (new);
}

char **ft_correct(char **cmd, t_list *lst)
{
    size_t  i;
    size_t  j;
    char    *tmp;
    char    **stmp;

    i = 0;
    j = 0;
    while (cmd[i])
    {
        if (ft_containvarenv(cmd[i]))
            cmd[i] = ft_cleancmd(ft_lst_toa(ft_lst_split(cmd[i], "$", 0)), lst);
        cmd[i] = ft_strtrim_quote(cmd[i]);
        i++;
    }
    return (cmd);
}




//MA VERSION :

char* ft_find_env(char *str, t_list *env)
{
    char *value;

    str = ft_strjoin(str, "=");
    value = NULL;
    while (env)
    {
        if(!ft_strlcmp(str, env->content))
        {
            value = ft_substr(env->content, ft_strlen(str), ft_strlen(env->content));
            return(value);
        }
        env = env->next;
    }
    return (0);
}

int     ft_strstri(const char *s1, const char *s2)
{
	size_t	size;
    size_t  len;
	char	*hay;
	char	*needle;
    int     i;

	hay = (char *)s1;
	needle = (char *)s2;
    i = 0;
    len = ft_strlen(hay);
	size = ft_strlen(needle);
	while (*hay && len >= size)
	{
		if (ft_strncmp(hay, needle, size) == 0)
			return (i);
		hay++;
		len--;
        i++;
	}
	return (-1);
}

char* ft_strrep(char *str, char *to_rep, char *rep)
{
    char *new;

    while(ft_strstri(str, to_rep) >= 0)
    {      
        new = ft_substr(str, 0, ft_strstri(str, to_rep));
        new = ft_strjoin(new, rep);
        new = ft_strjoin(new, ft_substr(str, ft_strstri(str, to_rep) + ft_strlen(to_rep), ft_strlen(str)));
        str = new;
    }
    return (str);
}

int        ft_isend(char c)
{
    return (ft_isspace(c) || !c || c == '"' || c == '\'' || c == '$');
}

char *ft_find_toreplace(char *str)
{
    char    quote;
    char    prev;
    char    *to_replace;
    int     k;

    quote = 0;
    prev = 0;
    k = 1;
    while (*str)
    {
        quote_inside(&quote, *str, prev);
        if (prev != '\\' && *str == '$' && quote != '\'')
        {
            while (!ft_isend(*(str + k)))
                k++;
            return (ft_substr(str, 0, k));
        }
        prev = *str;
        str++;
    }
    return(NULL);
}

char *ft_replace_env(char *str, t_list *env)
{
    char *to_rep;

    while((to_rep = ft_find_toreplace(str)))
        str = ft_strrep(str, to_rep, ft_find_env(to_rep + 1, env));
    return (str);
}