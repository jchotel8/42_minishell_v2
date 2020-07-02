/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_env(char **cmd, t_list **env)
{
	if (cmd && cmd[1])
	{
<<<<<<< HEAD:srcs/env_unset.c
		miniprinte("env: \"%s\": ", cmd[1]);
		miniprinte("Aucun fichier ou dossier de ce type\n");
=======
		miniprintf("env: \"%s\": Aucun fichier oudossier de ce type\n", cmd[1]);
>>>>>>> d11254e3121079b9c845c5a920cf0ca2e5c3637d:srcs/env_unset_export.c
		return (127);
	}
	ft_lstprint_if(*env, (void *)'=', ft_strchr);
	return (0);
}

int		ft_unset(char **cmd, t_list **env)
{
	size_t	i;
	char	*tmp;

	i = 1;
	while (cmd[i] && ft_strcmp(cmd[i], ""))
	{
		tmp = cmd[i];
		cmd[i] = ft_strjoin(cmd[i], "=");
		if (!check_export(cmd[i]))
		{
			miniprinte("export: '%s': not a valid identifier\n", tmp);
			return (8);
		}
		free(tmp);
		ft_lstremove_if(env, cmd[i], ft_strlcmp);
		i++;
	}
	return (0);
}
