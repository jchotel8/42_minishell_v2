/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:25:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putarray(char **array, char *text, int flag)
{
	int	i;

	i = 0;
	if (flag == 2)
		ft_putstr(text);
	while (array && array[i])
	{
		if (flag == 1)
			miniprintf("%s [%d] %s.\n", text, i, array[i]);
		else if (flag == 2)
			miniprintf("\"%s\" "array[i]);
		else
			miniprintf("%s %s.\n", text, array[i]);
		i++;
	}
	if (flag == 2)
		ft_putstr("\n");
}
