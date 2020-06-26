#include "../includes/minishell.h"

void    ft_putnstr(char *str, size_t start)
{
	size_t i;

	i = 0;
	while (str[i++])
		if (i >= start)
			ft_putchar(str[i]);
}

size_t  ft_strlenif(char *str, char c)
{
	size_t  i;
	size_t  j;
	size_t  s;

	i = 0;
	j = 0;
	s = 0;
	while (str[i])
	{
		if (str[i++] == c)
			s = 1;
		else if (s == 1)
			j++;
		i++;
	}
	return (j);
}

int     ft_echo(char **cmd, t_list *env)
{
	size_t  i;
	int     n_flag;

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

int    ft_pwd()
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		miniprintf("%s\n", cwd);
		return (0);
	}
	ft_putstr("Failed to get pwd");
	return (1);
}

char *get_wd()
{
	char    cwd[1024];
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
		return(ft_strdup("no WD"));
}

int ft_cd(char **cmd, t_list *env)
{
	if (cmd[2])
		miniprintf("cd: too many arguments\n");
	else if (chdir(cmd[1]) == -1)
	{
		miniprintf("cd: no such file or directory : %s\n", cmd[1]);
		return (8);
	}
	return (0);
}
