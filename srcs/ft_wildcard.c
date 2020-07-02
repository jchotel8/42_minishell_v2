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

#include "minishell.h"

char	*ft_getdir(void)
{
	struct dirent	*var;
	char			*tmp;
	DIR				*dir;

	dir = opendir(".");
	tmp = NULL;
	while ((var = readdir(dir)))
		if (var->d_name[0] != '.')
		{
			tmp = ft_strjoinf(tmp, var->d_name);
			tmp = ft_strjoinf(tmp, " ");
		}
	closedir(dir);
	return (tmp);
}

char	*ft_wildcard(char *str)
{
	char	*tmp;
	char	*dir;

	dir = ft_getdir();
	tmp = ft_strrep(str, ft_strdup("*"), dir);
	str = tmp;
	return (str);
}
