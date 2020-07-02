/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strstri(const char *s1, const char *s2)
{
	size_t	size;
	size_t	len;
	char	*hay;
	char	*needle;
	int		i;

	hay = (char *)s1;
	needle = (char *)s2;
	i = 0;
	len = ft_strlen(hay);
	size = ft_strlen(needle);
	while (*hay && len >= size)
	{
		if (ft_strncmp(hay, needle, size) == 0)
			return (i);
		hay++;
		len--;
		i++;
	}
	return (-1);
}

char	*ft_strrep(char *str, char *to_rep, char *rep)
{
	char	*new;
	char	*tmp;
	int		i;

	while ((i = ft_strstri(str, to_rep)) >= 0)
	{
		new = ft_substr(str, 0, i);
		new = ft_strjoinf(new, rep);
		tmp = ft_substr(str, i + ft_strlen(to_rep), ft_strlen(str)
		- i - ft_strlen(to_rep));
		new = ft_strjoinf(new, tmp);
		free(tmp);
		free(str);
		str = new;
	}
	free(to_rep);
	free(rep);
	return (str);
}

int		ft_isend(char c)
{
	return (ft_isspace(c) || !c || c == '"' || c == '\'' ||
	c == '$' || c == '=');
}

int		ft_isulsign(char c)
{
	if ((c == '<' || c == '>'))
		return (1);
	return (0);
}

t_list	*ft_lstrep(t_list *prev, t_list *add, t_list *rep)
{
	t_list	*next;

	next = rep->next;
	free(rep->content);
	free(rep);
	if (add)
	{
		if (prev)
			prev->next = add;
		ft_lstadd_back(&add, next);
		return (add);
	}
	if (prev)
		prev->next = next;
	return (next);
}
