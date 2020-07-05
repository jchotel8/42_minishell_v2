/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strfind(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		check_binary(char *file)
{
	int		fd;
	char	*read;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	get_next_line(fd, &read);
	while (read[i])
	{
		if (!ft_isascii(read[i]))
		{
			free(read);
			close(fd);
			return (1);
		}
		i++;
	}
	free(read);
	close(fd);
	return (0);
}

// void	handle_shlvl(t_list **env)
// {
// 	char *shlvl;
// 	char *newval;

// 	shlvl = ft_env_value("SHLVL", *env);
// 	newval = ft_itoa(ft_atoi(shlvl) + 1);
// 	handle_export(ft_strjoin("SHLVL=", newval), env, NULL);
// 	free(shlvl);
// 	free(newval);
// }
