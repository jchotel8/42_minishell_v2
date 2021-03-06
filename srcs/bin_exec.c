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

#include "minishell.h"

int		ft_find_bin(char **cmd, t_list *env, t_list *paths)
{
	char		*new;
	struct stat	buf;

	if (!stat(cmd[0], &buf) && S_ISREG(buf.st_mode) && check_binary(cmd[0]))
		return (execve(cmd[0], cmd, ft_lst_toa(env)));
	while (paths)
	{
		new = ft_strjoinf(ft_strjoin(paths->content, "/"), cmd[0]);
		if (!stat(new, &buf) && S_ISREG(buf.st_mode) && check_binary(new))
			return (execve(new, cmd, ft_lst_toa(env)));
		if (new != NULL)
			free(new);
		paths = paths->next;
	}
	miniprinte("Command not found: %s\n", cmd[0]);
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
			{
				ft_lstclear(&paths, *free);
				return (ret);
			}
			ft_lstclear(&paths, *free);
		}
		env_ = env_->next;
	}
	return (1);
}

int		ft_mybin(char **cmd, t_list **env)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, env));
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, env));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, env));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, env));
	else if (!ft_strcmp(cmd[0], "exit"))
		exit(0);
	else
		return (-1);
}

/*
** ft_exec and ft_exec2 returns :
** - 0 if mybin succeed
** - 8 if mybin fails
** - else ft_mybin returns -1
** - NA if execve succeed
** - -1 if fail
** - 127 if not found
*/

int		ft_exec(char **cmd, t_list **env)
{
	int ret;

	if (!(ret = ft_mybin(cmd, env)) || ret == 8)
		g_rep = ret;
	else
		g_rep = ft_bin(cmd, *env);
	g_rep <= 0 ? exit(0) : 0;
	g_rep == 8 ? exit(1) : 0;
	g_rep == 127 ? exit(3) : 0;
	return (g_rep);
}

int		ft_exec2(char **cmd, t_list **env)
{
	pid_t	pid;
	int		ret;

	if (!(ret = ft_mybin(cmd, env)) || ret == 8)
		return (ret);
	if (!(pid = fork()))
	{
		ret = ft_bin(cmd, *env);
		return (ret);
	}
	waitpid(pid, &ret, 0);
	return (ret);
}
