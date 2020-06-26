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

char	*ft_rdirectory(char *str)
{
	struct dirent	*var;
	char			*tmp;
	char			*array;
	DIR				*dir;

	dir = opendir(".");
	while ((var = readdir(dir)))
	{
		tmp = ft_strdup(var->d_name);
		array = ft_strjoin(array, tmp);
	}
	closedir(dir);
	return (tmp);
}