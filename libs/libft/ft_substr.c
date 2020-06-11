/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:55:12 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	int		index;
	char	*new_str;

	index = 0;
	if (!(new_str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[start] && len)
	{
		new_str[index] = str[start];
		len--;
		start++;
		index++;
	}
	new_str[index] = 0;
	return (new_str);
}
