/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exec.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_find_bin(char **cmd, t_list *env, t_list *paths)
{
	char		*new;
	char		*tmp;
	struct stat	buf;

	if (!stat(cmd[0], &buf))
		return (execve(cmd[0], cmd, ft_lst_toa(env)));
	while (paths)
	{
		tmp = ft_strjoin(paths->content, "/");
		new = ft_strjoin(tmp, cmd[0]);
		if (!stat(new, &buf))
		{
			free(new);
			free(tmp);
			return (execve(new, cmd, ft_lst_toa(env)));
		}
		paths = paths->next;
	}
	free(new);
	free(tmp);
	miniprintf("Command not found: %s\n", cmd[0]);
	return (127);
}

int		ft_bin(char **cmd, t_list *env)
{
	t_list	*paths;
	t_list	*env_;
	int		ret;

	env_ = env;
	while (env_)
	{
		if (!ft_strlcmp("PATH=", env_->content))
		{
			paths = ft_lst_split(env_->content + 5, ":", 1);
			if ((ret = ft_find_bin(cmd, env, paths)))
				return (ret);	
		}
		env_ = env_->next;
	}
	free(paths);
	free(cmd);
	return (1);
}

int		ft_mybin(char **cmd, t_list **env)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd, *env));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, env));
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, env));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, env));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, *env));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, *env));
	else
		return (-1);
}

int		ft_exec(char **cmd, t_list **env)
{
	int ret;

	if (!(ret = ft_mybin(cmd, env)) || ret == 8)
		return (ret); //renvoi 0 ou 8 si un des bins (S/F) sinon -1
	return (ft_bin(cmd, *env));// NA if success, -1 if fail, 127 if not found, 1 if ?
}

int		ft_exec2(char **cmd, t_list **env)
{//chaque fonction return 0, sauf dans le cas du ft_bin-> -1 si echec
	pid_t	pid;
	int		ret;

	if (!(ret = ft_mybin(cmd, env)) || ret == 8)
		return (ret);
	if (!(pid = fork()))
		return (ft_bin(cmd, *env));
	return (0);
}
