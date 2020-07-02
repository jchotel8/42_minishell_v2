/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:35:42 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstremove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list		*before;
	t_list		*current;

	current = *begin_list;
	while (current && (*cmp)(data_ref, current->content) == 0)
	{
		*begin_list = current->next;
		free(current->content);
		free(current);
		current = current->next;
	}
	before = current;
	while (current)
	{
		if ((*cmp)(data_ref, current->content) == 0)
		{
			before->next = current->next;
			free(current->content);
			free(current);
		}
		before = current;
		current = current->next;
	}
}
