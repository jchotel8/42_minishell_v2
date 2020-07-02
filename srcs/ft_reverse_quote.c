/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspecial(char c)
{
	return (c == '\\' || c == '\"');
}

void	ft_doublequote(char *s, char *new, int *i, int *j)
{
	new[*j++] = s[*i++];
	new[*j++] = (!ft_isspecial(s[*i]) ? '\\' : s[*i++]);
}

void	ft_simplequote(char *s, char *new, int *i, int *j)
{
	new[*j++] = (!ft_isspecial(s[*i + 1]) ||
	(s[*i + 1] != '\\' && ft_isspecial(s[*i + 1])) ? '\\' : s[*i++]);
	new[*j++] = s[*i++];
}

void	ft_noquote(char *s, char *new, int *i, int *j)
{
	if (!ft_isspecial(s[*i + 1]))
		(*i)++;
	else
	{
		new[(*j)++] = s[(*i)++];
		new[(*j)++] = s[(*i)++];
	}
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
	s[0] != '\"' ? new[j++] = '\"' : 0;
	s[0] == '\'' ? i++ : 0;
	(s[0] == '\"' || s[0] == '\'') ? quote = s[0] : 0;
	while (s[i])
		if (s[i] == '\\' && quote == '\"')
			ft_doublequote(s, new, &i, &j);
		else if (ft_isspecial(s[i]) && quote == '\'')
			ft_simplequote(s, new, &i, &j);
		else if (s[i] == '\'' && quote == '\'')
			i++;
		else if (s[i] == '\\')
			ft_noquote(s, new, &i, &j);
		else
			new[j++] = s[i++];
	quote != '\"' ? new[j] = '\"' : 0;
	return (new);
}
