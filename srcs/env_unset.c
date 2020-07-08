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

#include "minishell.h"

int		ft_env(char **cmd, t_list **env)
{
	if (cmd && cmd[1])
	{
		miniprinte("env: \"%s\": ", cmd[1]);
		miniprinte("Aucun fichier ou dossier de ce type\n");
		return (127);
	}
	ft_lstprint_if(*env, (void *)'=', ft_strchr);
	return (0);
}

int		ft_unset(char **cmd, t_list **env)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strlen(cmd[i]) == 0 || !check_export(cmd[i]))
		{
			miniprinte(ERR_MSG_UN, cmd[i]);
			return (8);
		}
		ft_lstremove_if(env, cmd[i], ft_strcmp);
		cmd[i] = ft_strjoinf(cmd[i], "=");
		ft_lstremove_if(env, cmd[i], ft_strlcmp);
		i++;
	}
	return (0);
}
