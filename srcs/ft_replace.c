/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_value(char *str, t_list *env)
{
	char *tmp;

	str = ft_strjoin(str, "=");
	while (env)
	{
		if (!ft_strlcmp(str, env->content))
		{
			tmp = ft_substr(env->content, ft_strlen(str),
			ft_strlen(env->content));
			free(str);
			return (tmp);
		}
		env = env->next;
	}
	free(str);
	return (0);
}

char	*ft_find_toreplace(char *str)
{
	char	quote;
	char	prev;
	int		k;

	quote = 0;
	prev = 0;
	k = 1;
	if (prev != '\\' && (!ft_strlcmp("~", str) || !ft_strncmp(str, "~/", 2)) && quote != '\'')
		return (ft_substr(str, 0, 1));
	while (*str)
	{
		quote_inside(&quote, *str, prev);
		if (prev != '\\' && *str == '$' && quote != '\'')
		{
			while (!ft_isend(*(str + k)))
				k++;
			if (k == 1)
				return (NULL);
			return (ft_substr(str, 0, k));
		}
		prev = *str;
		str++;
	}
	return (NULL);
}

/*
** WEXITSTATUS(ret) ?
** 768 - 127 cmd not found
** 256 - 1   fail bin (cat) || failed pipe
** 512 - 2   failed bin (ls grep)
** 8   - 1   one of my bin failed
** XXX - 130 ^C
*/

char	*ft_replace_env(char *str, t_list *env)
{
	char *to_rep;

	rep = (rep == 2 ? 130 : rep);
	rep = (rep == 768 ? 127 : rep);
	rep = (rep == 256 ? 1 : rep);
	rep = (rep == 512 ? 2 : rep);
	rep = (rep == 8 ? 1 : rep);
	while ((to_rep = ft_find_toreplace(str)))
	{
		if (!ft_strcmp(to_rep, "$?"))
			str = ft_strrep(str, to_rep, ft_itoa(rep));
		else if (!ft_strcmp(to_rep, "$"))
			return (str);
		else if (!ft_strcmp(to_rep, "~"))
			str = ft_strrep(str, to_rep, ft_env_value("HOME", env));
		else
			str = ft_strrep(str, to_rep, ft_env_value(to_rep + 1, env));
	}
	return (str);
}
