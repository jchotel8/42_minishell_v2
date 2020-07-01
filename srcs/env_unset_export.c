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
		miniprinte("env: \"%s\": Aucun fichier ou dossier de ce type\n", cmd[1]);
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
	char	*key;
	char	*val;

	if (ft_strfind(str, '=') == -1)
		return (str);
	key = ft_substr(str, 0, ft_strfind(str, '=') + 1);
	val = ft_substr(str, ft_strfind(str, '=') + 1, ft_strlen(str));
	add = ft_reverse_quote(val);
	new = ft_strjoinf(key, add);
	free(str);
	free(add);
	free(val);
	return (new);
}

int		ft_export(char **cmd, t_list **env)
{
	int		i;
	char	c;
	char	*tmp;
	t_list	*cpy;
	t_list 	*tmpc;
	int		flag;

	flag = 0;
	i = 1;
	if (cmd && cmd[i])
	{
		while (cmd[i])
		{
			if (check_export(cmd[i]))
			{
				if (ft_strfind(cmd[i], '=') >= 0)
				{
					tmp = ft_substr(cmd[i], 0, ft_strfind(cmd[i], '=') + 1);
					ft_lstremove_if(env, tmp, ft_strlcmp);
					free(tmp);
				}
				else if (ft_find_env(cmd[i], *env))
					flag = 1;
				if (!flag)
				{
					cmd[i] = ft_strtrim_quote(set_to_export(cmd[i]));
					ft_lstadd_back(env, ft_lstnew(ft_strdup(cmd[i])));
				}
				i++;
			}
			else
			{
				miniprinte("export: '%s': not a valid identifier\n", cmd[i++]);
				return (8);
			}
		}
	}
	else
	{
		cpy = ft_lstcpy(*env);
		ft_lstsort(cpy, ft_strcmp);
		tmpc = cpy;
		while (tmpc)
		{
			tmpc->content = set_to_export(tmpc->content);
			miniprintf("declare -x %s\n", tmpc->content);
			tmpc = tmpc->next;
		}
		ft_lstclear(&cpy, *free);
	}
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
			miniprinte("export: '%s': not a valid identifier\n", tmp);
			return (8);
		}
		free(tmp);
		ft_lstremove_if(env, cmd[i], ft_strlcmp);
		i++;
	}
	return (0);
}
