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
#include <stdio.h>

void	ft_lst_print(t_list *ptr, int flag)
{
	int	i = 0;

	if (ptr)
	{
		if (flag == 1)
			ft_printf("[%d] : %s\n", i, (char *)ptr->content);
		else if (flag == 2)
			ft_printf("\"%s\" ", (char *)ptr->content);
		else
			ft_printf("%s\n",(char *) ptr->content);
		while(ptr->next)
		{
			ptr = ptr->next;
			i++;
			if (flag == 1)
				ft_printf("[%d] : %s\n", i, (char *)ptr->content);
			else if (flag == 2)
				ft_printf("\"%s\" ", (char *)ptr->content);
			else
				ft_printf("%s\n",(char *) ptr->content);
		}
		if (flag == 2)
			ft_printf("\n");
	}
}