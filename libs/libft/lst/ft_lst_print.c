/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:01:29 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lst_print(t_list *ptr, int flag)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr)
		{
			if (flag == 1)
				miniprintf("[%d] : %s\n", i, (char *)ptr->content);
			else if (flag == 2)
				miniprintf("\"%s\" ", (char *)ptr->content);
			else
				miniprintf("%s\n", (char *)ptr->content);
			ptr = ptr->next;
			i++;
		}
		if (flag == 2)
			miniprintf("\n");
	}
}
