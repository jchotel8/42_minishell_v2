/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:06:10 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int		fnr(char *mem, int code)
{
	free(mem);
	mem = NULL;
	return (code);
}

int		get_next_char(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	if (str[index] == c)
		return (index);
	return (-1);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	j = 0;
	if (!(joined = ft_calloc((get_next_char(s1, '\0')
	+ get_next_char(s2, '\0')) + 1, sizeof(char))))
		return (NULL);
	while (s1[j])
	{
		joined[i] = s1[j];
		j++;
		i++;
	}
	free(s1);
	j = 0;
	while (s2[j])
	{
		joined[i] = s2[j];
		j++;
		i++;
	}
	joined[i] = 0;
	return (joined);
}
