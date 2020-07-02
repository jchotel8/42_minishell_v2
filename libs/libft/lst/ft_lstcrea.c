/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcrea.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:01:29 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

t_list	*ft_lstcrea(int i, ...)
{
	va_list		va;
	t_list		*first;

	first = NULL;
	va_start(va, i);
	while (i-- > 0)
	{
		ft_lstadd_back(&first, ft_lstnew(va_arg(va, void *)));
	}
	va_end(va);
	return (first);
}
