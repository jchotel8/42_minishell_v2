/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_export_print(t_list **env)
{
	t_list	*cpy;
	t_list	*tmp;

	cpy = ft_lstcpy(*env);
	ft_lstsort(cpy, ft_strcmp);
	tmp = cpy;
	while (tmp)
	{
		tmp->content = set_to_export(tmp->content);
		miniprintf("declare -x %s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&cpy, *free);
}

int		handle_export(char *cmd, t_list **env)
{
	char *tmp;

	if (check_export(cmd))
	{
		if (ft_strfind(cmd, '=') >= 0)
		{
			tmp = ft_substr(cmd, 0, ft_strfind(cmd, '=') + 1);
			ft_lstremove_if(env, tmp, ft_strlcmp);
			free(tmp);
			tmp = ft_substr(cmd, 0, ft_strfind(cmd, '='));
			ft_lstremove_if(env, tmp, ft_strlcmp);
		}
		if (ft_strfind(cmd, '=') >= 0 || !(tmp = ft_find_env(cmd, *env)))
		{
			cmd = ft_strtrim_quote(set_to_export(cmd));
			ft_lstadd_back(env, ft_lstnew(ft_strdup(cmd)));
		}
		free(tmp);
	}
	else
	{
		miniprinte("export: '%s': not a valid identifier\n", cmd);
		return (8);
	}
	free(cmd);
}

int		ft_export(char **cmd, t_list **env)
{
	int		i;
	char	c;
	char	*tmp;
	t_list	*cpy;

	i = 0;
	if (cmd && cmd[i + 1])
	{
		while (cmd[++i])
			if (handle_export(ft_strdup(cmd[i]), env) == 8)
				return (8);
	}
	else
		ft_export_print(env);
	return (0);
}
