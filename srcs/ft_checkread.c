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

int		ft_checkredir(char *read, int *i, int *s)
{
	while (ft_isspace(read[*i]))
		(*i)++;
	if (ft_isulsign(read[*i]) || read[*i] == 0)
	{
		if (read[*i] != 0)
			miniprintf("minishell : "ERR_MSG_C, read[*i]);
		else
			miniprintf("minishell : "ERR_MSG_S, "newline");
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
	while (read[i])
	{
		quote_inside(&quote, read[i], prev);
		if (count_signs(quote, read, &i, &s))
			return (0);
		else if (s > 0 && ft_checkredir(read, &i, &s))
			return (0);
		if (ft_checkpipe(read, &i))
			return (0);
		prev = read[i];
		i++;
	}
	return (1);
}
