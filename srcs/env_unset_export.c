#include "../includes/minishell.h"

/*
**	var="bonjour\toi" -> "bonjour\\toi";
**	var="bonjour\\toi" -> "bonjour\\toi";
**	var="bonjour\"toi" -> "bonjour\"toi";
**	var="bonjour\'toi" -> "bonjour\\'toi";
**	var="bonjour'toi" -> "bonjour'toi";
**
**	var=bonjour\toi -> "bonjourtoi";
**	var=bonjour\\toi -> "bonjour\\toi";
**	var=bonjour\"toi -> "bonjour\"toi";
**	var=bonjour\'toi -> "bonjour'toi";
**	var=bonjour\ toi -> "bonjour toi";
**	var=bonjour"toi -> retour_ligne;
**	
**	var='bonjour\toi' -> "bonjour\\toi";
**	var='bonjour\\toi' -> "bonjour\\\\toi";
**	var='bonjour\"toi' -> "bonjour\\\"toi";
**	var='bonjour"toi' -> "bonjour\"toi";
**	var='bonjour\'toi' -> retour a la ligne;
*/

int		ft_env(char **cmd, t_list **env)
{   //env /home : erreur 126 denied acces
	if (cmd && cmd[1])
	{
		miniprintf("env: \"%s\": Aucun fichier ou dossier de ce type\n", cmd[1]);
		return (127);
	}
	ft_lstprint_if(*env, (void *)'=', ft_strchr);
	return (0);
}

int		check_export(char *s)
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

int		ft_isspecial(char c)
{
	return (c == '\\' || c == '\"');
}

char	*ft_reverse_quote(char *s)
{
	int		i;
	int		j;
	char	quote;
	char	*new;

	i = 0;
	j = 0;
	quote = 0;
	new = ft_calloc(ft_strlen(s) * 2 + 2, sizeof(char));
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
			new[j++] = (!ft_isspecial(s[i + 1]) || (s[i + 1] != '\\' && ft_isspecial(s[i + 1])) ? '\\' : s[i++]);
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

int		ft_strfind(char *str, char c)
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

char	*set_to_export(char *str)
{
	char	*new;
	char	*add;
	char	*fst;
	char	*arg;

	if (ft_strfind(str, '=') == -1)
		return (str);
	fst = ft_substr(str, 0, ft_strfind(str, '=') + 1);
	arg = ft_substr(str, ft_strfind(str, '=') + 1, ft_strlen(str));
	add = ft_reverse_quote(arg);
	new = ft_strjoin(fst, add);
	free(str);
	free(fst);
	free(add);
	free(arg);
	return (new);
}

int		ft_export(char **cmd, t_list **env)
{
	int		i;
	char	c;
	t_list	*cpy;

	i = 1;
	cpy = ft_lstcpy(*env);
	if (cmd && cmd[i])
	{
		while (cmd[i])
		{
			if (check_export(cmd[i]))
			{
				ft_lstremove_if(env, ft_substr(cmd[i], 0, ft_strfind(cmd[i], '=') + 1), ft_strlcmp);
				ft_lstadd_back(env, ft_lstnew(ft_strtrim_quote(set_to_export(cmd[i++]))));
			}
			else
			{
				miniprintf("export: '%s': not a valid identifier\n", cmd[i++]);
				return (8);
			}
		}
	}
	else
	{
		ft_lstsort(cpy, ft_strcmp);
		t_list *tmp;
		tmp = cpy;
		while (tmp)
		{
			tmp->content = set_to_export(tmp->content);
			miniprintf("declare -x %s\n", tmp->content);
			tmp = tmp->next;
		}
		ft_lstclear(&cpy, *free);
	}
	//	ft_lst_print(ft_lstsort(cpy, ft_strcmp), 3);
	return (0);
}

int		ft_unset(char **cmd, t_list **env)
{
	size_t	i;
	char	*tmp;

	i = 1;
	while (cmd[i] && ft_strcmp(cmd[i], ""))
	{
		tmp = cmd[i];
		cmd[i] = ft_strjoin(cmd[i], "=");
		if (!check_export(cmd[i]))
		{
			miniprintf("export: '%s': not a valid identifier\n", tmp);
			return (8);
		}
		free(tmp);
		ft_lstremove_if(env, cmd[i], ft_strlcmp);
		i++;
	}
	return (0);
}
