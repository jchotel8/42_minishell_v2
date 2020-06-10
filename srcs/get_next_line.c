/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:37:32 by llepage           #+#    #+#             */
/*   Updated: 2019/12/02 13:00:01 by llepage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(tmp = ft_calloc((ft_strlen(s1, 1) +
	ft_strlen(s2, 1) + 1), sizeof(char))))
		return (NULL);
	while (s1 && s1[i])
		tmp[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		tmp[j++] = s2[i++];
	tmp[j] = 0;
	s1 = ft_strdup(tmp, s1);
	return (s1);
}

char	*ft_correct(char *save, char **line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = ft_calloc((ft_strlen(save, 2) + 1), sizeof(char))))
		return (NULL);
	while (save[i] && save[i] != '\n')
	{
		tmp[i] = save[i];
		i++;
	}
	tmp[i] = 0;
	*line = ft_strdup(tmp, *line);
	return (*line);
}

int		ft_exit(int c, char **buffer, char **save, char **line)
{
	if (c >= 0)
	{
		if (*buffer)
			free(*buffer);
		if (*save)
		{
			free(*save);
			*save = NULL;
		}
		if (c == 0)
			*line = ft_calloc(1, sizeof(char));
		if (c == 2)
			return (0);
	}
	if (c == -1)
		if (!*buffer)
			free(*buffer);
	return (c);
}

int		ft_process(char **line, char **save, char **stock, int type)
{
	if (type == 1)
	{
		*save = ft_strjoin(*save, *stock);
		*stock = ft_clear(*stock, 1);
	}
	else if (type == 2)
	{
		*line = ft_correct(*save, line);
		*save = ft_clear(*save, 2);
		free(*stock);
		return (1);
	}
	else
	{
		*line = ft_correct(*save, line);
		return (ft_exit(2, stock, save, line));
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			*stock;
	static char		*save;
	int				r;

	if (fd < 0 || BUFFER_SIZE <= 0 ||
	!line || !(stock = ft_calloc((BUFFER_SIZE + 1), sizeof(char))))
		return (ft_exit(-1, &stock, &save, line));
	ft_before(&save, line);
	if (ft_strlen(save, 3) == 0)
	{
		while ((r = read(fd, stock, BUFFER_SIZE)) > 0)
		{
			ft_process(line, &save, &stock, 1);
			if (ft_strlen(save, 3) > 0)
				return (ft_process(line, &save, &stock, 2));
		}
		if (r == 0 && ft_strlen(save, 1) > 0)
			return (ft_process(line, &save, &stock, 3));
		if (r < 0)
			return (ft_exit(-1, &stock, &save, line));
	}
	else
		return (ft_process(line, &save, &stock, 2));
	return (ft_exit(0, &stock, &save, line));
}
