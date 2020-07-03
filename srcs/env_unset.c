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
	char	*tmp;

	i = 1;
	while (cmd[i] && ft_strcmp(cmd[i], ""))
	{
		tmp = ft_strdup(cmd[i]);
		cmd[i] = ft_strjoinf(cmd[i], "=");
		if (!check_export(cmd[i]))
		{
			miniprinte("unset: '%s': not a valid identifier\n", tmp);
			if (tmp != NULL)
				free(tmp);
			return (8);
		
		}
		if (tmp != NULL)
			free(tmp);
		ft_lstremove_if(env, cmd[i], ft_strlcmp);
		i++;
	}
	return (0);
}
