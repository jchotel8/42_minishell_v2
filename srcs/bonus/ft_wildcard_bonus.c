/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_getdir(void)
{
	struct dirent	*var;
	DIR				*dir;
	t_list			*lst;

	dir = opendir(".");
	lst = NULL;
	while ((var = readdir(dir)))
		if (var->d_name[0] != '.')
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(var->d_name)));
	closedir(dir);
	return (lst);
}

void	ft_wildcard(t_list **lst)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*dir;
	char	*str;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		str = tmp->content;
		if(is_onlychar(str))
		{
			dir = ft_getdir();
			tmp = ft_lstrep(prev, dir, tmp);
		}
		!prev ? *lst = tmp : 0;
		prev = tmp;
		tmp = (tmp ? tmp->next : NULL);
	}
}
