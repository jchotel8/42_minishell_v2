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

#include "../includes/minishell.h"

char	*ft_find_env(char *str, t_list *env)
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
	char	*to_replace;
	int		k;

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
** cmd not found
** cat ndir || pipe
** ls ndir || grep
** one of my bin failed
** ^C 130
*/

char	*ft_replace_env(char *str, t_list *env)
{
	char *to_rep;

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
		else
			str = ft_strrep(str, to_rep, ft_find_env(to_rep + 1, env));
	}
	return (str);
}
