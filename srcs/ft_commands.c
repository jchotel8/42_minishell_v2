#include "../includes/minishell.h"

int     ft_echo(char **cmd)
{
    size_t i;

    if (cmd[1] == NULL)
    {
        ft_putchar('\n');
        return (1);
    }
    if (!ft_strcmp(cmd[1], "-n")) 
    {
        i = 2;
        while (cmd[i]) {
            if (i >= 3)
                ft_putchar(' ');
            ft_putstr(cmd[i++]);
        }
        return (1);
    }
    i = 1;
    while (cmd[i]) {
        if (i >= 2)
            ft_putchar(' ');
        ft_putstr(cmd[i++]);
    }
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
    int     i;

    i = 0;
    if (getcwd(cwd, sizeof(cwd)))
    {
        files = ft_split(cwd, '/');
        while (files && files[i])
		    i++;
        return (ft_strdup(files[i - 1]));
    }
    else
        return(ft_strdup("no WD"));
}

int ft_env (char **cmd, t_list *env)
{   //env /home : erreur 126 denied acces
    if (cmd && cmd[1])
    {
        miniprintf("env: \"%s\": Aucun fichier ou dossier de ce type\n", cmd[1]);
        return (127);
    }
    ft_lst_print(env, 0);
    return (0);
}

// int ft_unset(char **cmd, t_list *env)
// {

// }

char	check_export(char *s)
{
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '-'))
			return (*s);
		s++;
	}
	return (*s);
}

int ft_export(char **cmd, t_list *env)
{
    int     i;
    char    c;

    i = 1;
    if (cmd && cmd[i])
    {
        while(cmd[i])
        {
            if (!(c = check_export(cmd[i])))
                ft_lstadd_back(&env, ft_lstnew(cmd[i++]));
            else
            {
                miniprintf("export: '%s': not a valid identifier\n", cmd[i]);
                return (1);
            }
        }
    }
    else
    {
        miniprintf("need to print the list (and sort)\n");
    }
    return (0);
}


int     do_exec(char **cmd, t_list *env)
{
    if (!ft_strcmp(cmd[0], "echo"))
        return (ft_echo(cmd));
    else if (!ft_strcmp(cmd[0], "pwd"))
        return(ft_pwd());
    else if (!ft_strcmp(cmd[0], "env"))
        return(ft_env(cmd, env));
    else if (!ft_strcmp(cmd[0], "export"))
        return(ft_export(cmd, env));
    else if (execvp(cmd[0], cmd))
        return (1);
    return (0);
}