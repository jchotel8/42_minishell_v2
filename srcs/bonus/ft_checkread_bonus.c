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

char	*ft_checkquotes(char *read)
{
	char	*next;

	while (ft_countquote(read) % 2)
	{
		miniprintf(">");
		get_next_line(0, &next);
		read = ft_strjoinf(read, "\n");
		read = ft_strjoinf(read, next);
		free(next);
	}
	return (read);
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
		prev = read[i];
		i++;
	}
	return (1);
}
