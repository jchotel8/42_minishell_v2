/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lst_split(char *s, char *c, int i)
{
	t_list	*lst;
	char	*ptr;
	char	quote;
	char	prev;

	lst = NULL;
	ptr = s;
	quote = 0;
	prev = 0;
	if (!s)
		return (NULL);
	while (*s)
	{
		quote_inside(&quote, *s, prev);
		if (!quote && ft_strrchr(c, *s))
		{
			if (ptr != s)
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
			ptr = (char *)s + i;
		}
		prev = *s;
		s++;
	}
	ptr != s ? ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr))) : 0;
	return (lst);
}
