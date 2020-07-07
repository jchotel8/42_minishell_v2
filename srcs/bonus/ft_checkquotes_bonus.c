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
