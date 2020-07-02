/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	quote_inside(char *quote, char new, char prev)
{
	if (!*quote && prev != '\\' && (new == '\'' || new == '"'))
	{
		*quote = new;
		return (1);
	}
	else if ((new == '\'' || (new == '"' && prev != '\\')) && *quote == new)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int		trim_condition(char quote, char *s, int i, char prev)
{
	return ((!quote && s[i] == '\\' && prev != '\\') ||
		(quote == '"' && s[i] == '\\' &&
		((s[i + 1] == '\\' && prev != '\\') || s[i + 1] == '"')) ||
		(prev == '"' && s[i] == '"'));
}

char	*ft_strtrim_quote(char *s)
{
	int		i;
	int		j;
	char	quote;
	char	prev;
	char	*new;

	i = 0;
	j = 0;
	prev = 0;
	quote = 0;
	if (!(new = ft_calloc(ft_strlen(s), sizeof(char))))
		return (NULL);
	while (s[i])
	{
		if (quote_inside(&quote, s[i], prev) ||
		trim_condition(quote, s, i, prev))
			prev = s[i++];
		else
		{
			prev = 0;
			new[j++] = s[i++];
		}
	}
	free(s);
	return (new);
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
			new[j++] = (!ft_isspecial(s[i + 1]) ||
			(s[i + 1] != '\\' && ft_isspecial(s[i + 1])) ? '\\' : s[i++]);
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
