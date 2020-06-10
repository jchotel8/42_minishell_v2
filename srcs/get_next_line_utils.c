/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:37:46 by llepage           #+#    #+#             */
/*   Updated: 2019/12/02 12:59:38 by llepage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	ft_strlen(char *s, int type)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = 0;
	if (s == NULL)
		return (0);
	if (type == 1)
		while (s[i])
			i++;
	else if (type == 2)
		while (s[i] && s[i] != '\n')
			i++;
	else if (type == 3)
	{
		while (s[i])
		{
			if (s[i] == '\n')
				r++;
			i++;
		}
		return (r);
	}
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	if (count == 0)
		count = 1;
	if (!size || !(tmp = malloc(count * size)))
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)tmp)[i] = '\0';
		i++;
	}
	return (tmp);
}

char	*ft_strdup(char *src, char *dst)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!(tmp = ft_calloc((ft_strlen(src, 1) + 1), sizeof(char))))
		return (NULL);
	while (src[i])
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = 0;
	free(src);
	src = NULL;
	free(dst);
	return (tmp);
}

char	*ft_clear(char *s, int type)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (type == 1)
	{
		free(s);
		if (!(s = ft_calloc((BUFFER_SIZE + 1), sizeof(char))))
			return (NULL);
		return (s);
	}
	else
	{
		i = ft_strlen(s, 2) + 1;
		if (!(tmp = ft_calloc((ft_strlen(s, 1) - ft_strlen(s, 2)
		+ 1), sizeof(char))))
			tmp = NULL;
		while (s[i] && s)
			tmp[j++] = s[i++];
		tmp[j] = 0;
	}
	s = ft_strdup(tmp, s);
	return (s);
}

void	ft_before(char **save, char **line)
{
	if (*save == NULL)
		*save = ft_calloc(1, sizeof(char));
	*line = NULL;
	return ;
}
