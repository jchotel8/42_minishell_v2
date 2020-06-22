/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:45:35 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstsort(t_list *lst, int (*cmp)())
{
	void	*tmp_data;
	t_list	*tmp_lst;

	tmp_lst = lst;
	while (lst->next)
	{
		if (((*cmp)(lst->content, lst->next->content)) > 0)
		{
			tmp_data = lst->content;
			lst->content = lst->next->content;
			lst->next->content = tmp_data;
			lst = tmp_lst;
		}
		else
			lst = lst->next;
	}
	lst = tmp_lst;
	return (lst);
}