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

int		check_export(char *s)
{
	int flag;

	flag = 0;
	if (!(ft_isalpha(*s) || *s == '_'))
	{
		return (0);
	}
	while (*s && !flag)
	{
		if (*s == '=')
			flag = 1;
		if (!flag && (!(ft_isalnum(*s) || *s == '_')))
		{
			return (0);
		}
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
	//miniprintf("set to export : %s\n", new);
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

// int		handle_export(char *cmd, t_list **env, char *tmp)
// {
// 	char	*save;

// 	save = ft_strdup(cmd);
// 	if (check_export(cmd))
// 	{
// 		if (ft_strfind(cmd, '=') >= 0)
// 		{
// 			tmp = ft_substr(cmd, 0, ft_strfind(cmd, '=') + 1);
// 			ft_lstremove_if(env, tmp, ft_strlcmp);
// 			free(tmp);
// 			tmp = ft_substr(cmd, 0, ft_strfind(cmd, '='));
// 			ft_lstremove_if(env, tmp, ft_strlcmp);
// 		}
// 		if (ft_strfind(cmd, '=') >= 0 || !(tmp = ft_env_value(cmd, *env)))
// 			ft_lstadd_back(env, ft_lstnew(ft_strtrim_quote(set_to_export(cmd))));
// 		free(tmp);
// 	}
// 	else
// 	{
// 		miniprinte("export: '%s': not a valid identifier\n", save);
// 		free(save);
// 		return (8);
// 	}
// 	free(save);
// 	return (0);
// }

int		ft_env_condition(char *str, char *ref)
{
	if (ft_strfind(ref, '=') > -1 && !ft_strlcmp(ref, str))
		return (1);
	else if (ft_strfind(ref, '=') > -1 && ft_strfind(str, '=') < 0 &&
	!ft_strlcmp(str, ref) && ft_strlen(ref) - 1== ft_strlen(str))
		return (1);
	else if (ft_strfind(ref, '=') > -1)
		return (2);
	else if (!ft_strcmp(ref, str) || (!ft_strlcmp(ref, str) && str[ft_strlen(ref)] == '='))
		return (0);
	return (2);
}

int		handle_export(char *cmd, t_list **env, char *tmp)
{
	t_list *lst;
	int		i;
	char 	*key;
	(void) tmp;
	int j;

	j = 0;
	if (check_export(cmd))
	{
		if (ft_strfind(cmd, '=') >= 0 && (j = 1))
			key = ft_substr(cmd, 0, ft_strfind(cmd, '=') + 1);
		lst = *env;
		while(lst && (i = ft_env_condition(lst->content, key)) == 2)
			lst = lst->next;
		if (i == 2)
			ft_lstadd_back(env, ft_lstnew(ft_strtrim_quote(set_to_export(cmd))));
		if (i == 1)
		{
			free(lst->content);
			lst->content = ft_strtrim_quote(set_to_export(cmd));
		}
		if (i == 0)
			free(cmd);
		if (j == 1)
			free(key);
	}
	else
	{
		miniprinte("export: '%s': not a valid identifier\n", cmd);
		return (8);
	}
	return (0);
}

int		ft_export(char **cmd, t_list **env)
{
	int		i;

	i = 0;
	if (cmd && cmd[i + 1])
	{
		while (cmd[++i])
			if (handle_export(ft_strdup(cmd[i]), env, NULL) == 8)
				return (8);
	}
	else
		ft_export_print(env);
	return (0);
}
