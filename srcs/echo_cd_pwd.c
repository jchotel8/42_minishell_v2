/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **cmd)
{
	size_t	i;
	size_t	j;
	int		n_flag;

	i = 1;
	n_flag = 0;
	while (cmd[i] && cmd[i][0] == '-' && is_onlychar(cmd[i] + 1, 'n'))
	{
		i++;
		n_flag = 1;
	}
	j = i;
	while (cmd[i])
	{
		if (i > j)
			ft_putchar(' ');
		ft_putstr(cmd[i++]);
	}
	if (!n_flag)
		ft_putchar('\n');
	return (0);
}

int		ft_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		miniprintf("%s\n", cwd);
		return (0);
	}
	ft_putstr_fd("Failed to get pwd", 2);
	return (1);
}

char	*get_wd(void)
{
	char	cwd[1024];
	char	**files;
	char	*ret;
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)))
	{
		files = ft_split(cwd, '/');
		while (files && files[i])
			i++;
		if (i == 0)
			ret = ft_strdup("/");
		else
			ret = ft_strdup(files[i - 1]);
		ft_freearray(files);
		return (ret);
	}
	else
		return (ft_strdup("no WD"));
}

int		try_repo(char *cmd, char *to_free)
{
	if (chdir(cmd) != 0)
	{
		miniprinte("cd: no such file or directory : %s\n", cmd);
		free(to_free);
		return (1);
	}
	return (0);
}

int		ft_cd(char **cmd, t_list **env)
{
	char *tild;

	tild = "_";
	if (cmd[2] || (!(tild = ft_env_value("HOME", *env)) && cmd[1]))
	{
		cmd[2] ? miniprinte("minishell: cd: too many arguments\n") : 0;
		!cmd[2] ? miniprinte("minishell: cd: \"HOME\" non défini\n") : 0;
		return (8);
	}
	else if ((!cmd[1] || !ft_strcmp(cmd[1], "-")))
	{
		tild = ft_strtrim_quote(tild);
		(cmd[1] && !ft_strcmp(cmd[1], "-")) ? miniprintf("%s\n", tild) : 0;
		if (try_repo(tild, tild) == 1)
			return (8);
	}
	else if (try_repo(cmd[1], tild) == 1)
		return (8);
	free(tild);
	return (0);
}
