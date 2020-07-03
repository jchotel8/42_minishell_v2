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

#include "minishell.h"

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

int		ft_countquote(char *s)
{
	int		i;
	int		count;
	char	current;
	char	prev;

	prev = 0;
	current = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (quote_inside(&current, s[i], prev))
			count++;
		prev = s[i];
		i++;
	}
	return (count);
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
