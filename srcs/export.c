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

void	ft_rexport(t_list *tmpc, t_list *cpy, t_list **env)
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

int		ft_export(char **cmd, t_list **env)
{
	int		i;
	char	c;
	char	*tmp;
	t_list	*cpy;
	t_list	*tmpc;
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
		ft_rexport(tmpc, cpy, env);
	return (0);
}
