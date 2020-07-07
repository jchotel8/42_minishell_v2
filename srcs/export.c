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

#include "minishell.h"

char	*set_to_export(char *str, int flag)
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
	if (flag == 0)
		new = ft_strjoinf(key, add);
	else
	{
		new = ft_strjoinf(key, "\"");
		new = ft_strjoinf(new, add);
		new = ft_strjoinf(new, "\"");
	}
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
		tmp->content = set_to_export(tmp->content, 1);
		miniprintf("declare -x %s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&cpy, *free);
}

int		ft_env_condition(char *str, char *ref)
{
	if (ft_strfind(ref, '=') > -1 && !ft_strlcmp(ref, str))
		return (1);
	else if (ft_strfind(ref, '=') > -1 && ft_strfind(str, '=') < 0 &&
	!ft_strlcmp(str, ref) && ft_strlen(ref) - 1 == ft_strlen(str))
		return (1);
	else if (ft_strfind(ref, '=') > -1)
		return (2);
	else if (!ft_strcmp(ref, str) || (!ft_strlcmp(ref, str)
	&& str[ft_strlen(ref)] == '='))
		return (0);
	return (2);
}

int		handle_export(char *cmd, t_list **env)
{
	t_list	*lst;
	int		i;
	char	*key;
	int		j;

	if (!check_export(cmd) && (j = 0))
	{
		miniprinte("export: '%s': not a valid identifier\n", cmd);
		return (8);
	}
	if (ft_strfind(cmd, '=') >= 0 && (j = 1))
		key = ft_substr(cmd, 0, ft_strfind(cmd, '=') + 1);
	lst = *env;
	while (lst && (i = ft_env_condition(lst->content, key)) == 2)
		lst = lst->next;
	if (i == 2)
		ft_lstadd_back(env, ft_lstnew(ft_strtrim_quote(set_to_export(cmd, 0))));
	if (i == 1)
	{
		free(lst->content);
		lst->content = ft_strtrim_quote(set_to_export(cmd, 0));
	}
	i == 0 ? free(cmd) : 0;
	j == 1 ? free(key) : 0;
	return (0);
}

int		ft_export(char **cmd, t_list **env)
{
	int		i;

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
