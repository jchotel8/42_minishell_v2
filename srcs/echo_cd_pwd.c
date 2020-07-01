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

#include "../includes/minishell.h"

int		ft_echo(char **cmd, t_list *env)
{
	size_t	i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
	{
		i = 2;
		n_flag = 1;
	}
	while (cmd[i])
	{
		if ((i >= 2 && n_flag == 0) || (n_flag == 1 && i >= 3))
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
		ret = ft_strdup(files[i - 1]);
		ft_freearray(files);
		return (ret);
	}
	else
		return (ft_strdup("no WD"));
}

int		ft_cd(char **cmd, t_list *env)
{
	if (cmd[2])
		miniprinte("cd: too many arguments\n");
	else if (chdir(cmd[1]) == -1)
	{
		miniprinte("cd: no such file or directory : %s\n", cmd[1]);
		return (8);
	}
	return (0);
}
