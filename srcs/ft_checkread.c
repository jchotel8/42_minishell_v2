/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkread.c	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_signs(char quote, char *read, int *i, int *s)
{
	while (!quote && (read[*i] == '<' || read[*i] == '>'))
	{
		(*s)++;
		(*i)++;
	}
	if (*s > 2)
	{
		miniprintf("minishell : "ERR_MSG_C, read[*i - 1]);
		free(read);
		return (1);
	}
	return (0);
}

int		ft_checkredir(char *read, int *i, int *s, char prev)
{
	while (ft_isspace(read[*i]))
		(*i)++;
	if ((read[*i] == 0 || ft_isulsign(read[*i])) || prev == '\\')
	{
		if (read[*i] != 0)
			miniprintf("minishell : "ERR_MSG_C, read[*i]);
		else if (prev != '\\')
			miniprintf("minishell : "ERR_MSG_S, "newline");
		else if (prev == '\\') {
			miniprintf("NEED TO UPDATE\n");
			return (1);
		}
		free(read);
		return (1);
	}
	else
		*s = 0;
	return (0);
}

int		ft_checkpipe(char *read, int *i)
{
	int j;

	j = *i - 1;
	if (read[*i] == '|')
	{
		while (j >= 0 && ft_isspace(read[j]))
			j--;
		if (j <= 0 || read[j] == ';' || read[j] == '|')
		{
			miniprinte("minishell : "ERR_MSG_C, '|');
			free(read);
			return (1);
		}
		j = *i + 1;
		while (read[j] && ft_isspace(read[j]))
			j++;
		if (read[j] == ';')
		{
			miniprinte("minishell : "ERR_MSG_C, read[j]);
			free(read);
			return (1);
		}
	}
	return (0);
}

int		ft_checkparent(char quote, char *read, int *i, char prev)
{
	if ((read[*i] == '(' || read[*i] == ')') && (!quote && prev != '\\'))
	{
		miniprinte("minishell : "ERR_MSG_C, read[*i]);
		free(read);
		return (1);
	}
	return (0);
}

int		ft_checkread(char *read)
{
	int		i;
	int		s;
	char	prev;
	char	quote;

	s = 0;
	i = 0;
	quote = 0;
	while (read[i] && read)
	{
		quote_inside(&quote, read[i], prev);
		if (count_signs(quote, read, &i, &s))
			return (0);
		else if (s > 0 && ft_checkredir(read, &i, &s, prev))
			return (0);
		if (ft_checkpipe(read, &i))
			return (0);
		if (ft_checkparent(quote, read, &i, prev))
			return (0);
		prev = read[i];
		i++;
	}
	return (1);
}
