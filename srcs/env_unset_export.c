#include "../includes/minishell.h"


// var="bonjour\toi" -> "bonjour\\toi";
// var="bonjour\\toi" -> "bonjour\\toi";
// var="bonjour\"toi" -> "bonjour\"toi";
// var="bonjour\'toi" -> "bonjour\\'toi";
// var="bonjour'toi" -> "bonjour'toi";

// var=bonjour\toi -> "bonjourtoi";
// var=bonjour\\toi -> "bonjour\\toi";
// var=bonjour\"toi -> "bonjour\"toi";
// var=bonjour\'toi -> "bonjour'toi";
// var=bonjour\ toi -> "bonjour toi";
// var=bonjour"toi -> retour_ligne;

// var='bonjour\toi' -> "bonjour\\toi";
// var='bonjour\\toi' -> "bonjour\\\\toi";
// var='bonjour\"toi' -> "bonjour\\\"toi";
// var='bonjour"toi' -> "bonjour\"toi";
// var='bonjour\'toi' -> retour a la ligne;

int ft_env (char **cmd, t_list **env)
{   //env /home : erreur 126 denied acces
    if (cmd && cmd[1])
    {
        miniprintf("env: \"%s\": Aucun fichier ou dossier de ce type\n", cmd[1]);
        return (127);
    }
    ft_lstprint_if(*env, (void *)'=', ft_strchr);
    return (0);
}

int	check_export(char *s)
{
    int flag;

    flag = 0;
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	while (*s && !flag)
	{
        if (*s == '=')
            flag = 1;
		if (!flag && (!(ft_isalnum(*s) || *s == '_')))
			return (0);
		s++;
	}
    return (1);
}

int        ft_isspecial(char c)  //a ajouter dans la libft
{
    return (c == '\\' || c == '\"');
}

char *ft_reverse_quote(char *s)
{
	int i;
	int j;
	char quote;
	char *new;

	i = 0;
	j = 0;
    quote = 0;
	new = ft_calloc(ft_strlen(s)* 2 + 2, sizeof(char));
    if (s[0] != '\"')
        new[j++] = '\"';
    if (s[0] == '\'')
        i++;
    if (s[0] == '\"' || s[0] == '\'')
        quote = s[0];
	while (s[i])
	{
        if (s[i] == '\\' && quote == '\"')
        {
            new[j++] = s[i++];
            new[j++] = (!ft_isspecial(s[i]) ? '\\' : s[i++]);
        }
        else if (ft_isspecial(s[i]) && quote == '\'')
        {
            new[j++] = (!ft_isspecial(s[i + 1]) || (s[i + 1] !='\\' && ft_isspecial(s[i + 1]))? '\\' : s[i++]);
            new[j++] = s[i++];
        }
        else if (s[i] == '\'' && quote == '\'')
            i++;
        else if (s[i] == '\\')
        {
            if (!ft_isspecial(s[i + 1]))
                i++;
            else
            {
                new[j++] = s[i++];
                new[j++] = s[i++];
            }
        }
        else
	        new[j++] = s[i++];
	}
    quote != '\"' ? new[j] = '\"' : 0;
	return (new);
}

int ft_strfind(char *str, char c)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

char *test_export(char *str)
{
    char *new;
    char *add;

    if (ft_strfind(str, '=') == -1)
        return (str);
    new = ft_substr(str, 0, ft_strfind(str, '=') + 1);
    add = ft_reverse_quote(ft_substr(str, ft_strfind(str, '=') + 1, ft_strlen(str)));
    new = ft_strjoin(new, add);
    return (new);
}

int ft_export(char **cmd, t_list **env)
{
    int     i;
    char    c;
    t_list  *tmp;

    i = 1;
    tmp = ft_lstcpy(*env);
    if (cmd && cmd[i])
    {
        while(cmd[i])
        {
            if (check_export(cmd[i]))
            {
                    ft_lstremove_if(env, ft_substr(cmd[i], 0, ft_strfind(cmd[i], '=') + 1), ft_strlcmp);
                    ft_lstadd_back(env, ft_lstnew(test_export(cmd[i++])));
            }
            else
            {
                miniprintf("export: '%s': not a valid identifier\n", cmd[i++]);
            }
        }
    }
    else
		ft_lst_print(ft_lstsort(tmp, ft_strcmp), 3);
    //ft_lstclean(&tmp); FREE TMP 
    return (0);
}

int     ft_unset(char **cmd, t_list **env)
{
    size_t i;
    char   *tmp;

    i = 1;
    while (cmd[i] && ft_strcmp(cmd[i], ""))
    {
        tmp = cmd[i];
        cmd[i] = ft_strjoin(cmd[i], "=");
        free(tmp);
        ft_lstremove_if(env, cmd[i], ft_strlcmp);
        i++;
    }
    return (0);
}