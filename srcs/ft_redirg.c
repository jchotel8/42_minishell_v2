/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_rdirectory()
{
	struct dirent	*var;
	char			*array;
	char			*tmp;
	DIR				*dir;

	dir = opendir(".");
	array = NULL;
	while ((var = readdir(dir)))
		if (var->d_name[0] != '.')
		{
			tmp = ft_strjoin(array, var->d_name);
			array = ft_strjoin(tmp, " ");
			free(tmp);
		}
	closedir(dir);
	return (array);
}

size_t	ft_strlend(char **str)
{
	size_t i;

	i = 0;
	while (str[i] && str)
		i++;
	return (i);
}

char	*ft_parsestrdir(char *str)
{
	char	*tmp;
	char	*dir;
	
	dir = ft_rdirectory();
	tmp = ft_strrep(str, ft_strdup("*"), dir);
	str = tmp;
	return (str);
}