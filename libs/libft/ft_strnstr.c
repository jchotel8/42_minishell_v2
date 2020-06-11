/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:06:32 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	size;
	char	*hay;
	char	*needle;

	hay = (char *)s1;
	needle = (char *)s2;
	size = ft_strlen(needle);
	while (*hay && len >= size)
	{
		if (ft_strncmp(hay, needle, size) == 0)
			return (hay);
		hay++;
		len--;
	}
	return (0);
}
