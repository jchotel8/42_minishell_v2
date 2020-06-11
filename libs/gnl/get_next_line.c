/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:05:52 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_strnew(unsigned int len)
{
	char	*new;

	if (!(new = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	return (new);
}

int		checks(char **buffer, char **rest, char **line, int fd)
{
	if (BUFFER_SIZE <= 0 || !line || fd < 0 || fd > FD_MAX)
		return (0);
	if (!rest[fd] && !(rest[fd] = ft_calloc(1, sizeof(char *))))
		return (0);
	if (!(*buffer = ft_strnew(BUFFER_SIZE + 1)))
		return (0);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest[FD_MAX];
	char		*buffer;
	char		*tmp;
	int			ret;

	if (!checks(&buffer, rest, line, fd))
		return (-1);
	while (get_next_char(rest[fd], '\n') < 0
	&& (ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = 0;
		rest[fd] = ft_strjoin(rest[fd], buffer);
	}
	free(buffer);
	if (ret < 0)
		return (ret);
	*line = ft_substr(rest[fd], 0, get_next_char(rest[fd], '\n'));
	if (get_next_char(rest[fd], '\n') < 0)
		return (fnr(rest[fd], 0));
	tmp = rest[fd];
	rest[fd] = ft_substr(rest[fd], get_next_char(rest[fd], '\n')
	+ 1, get_next_char(rest[fd], '\0'));
	free(tmp);
	return (1);
}

