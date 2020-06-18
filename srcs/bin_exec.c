#include "../includes/minishell.h"

int ft_find_bin(char **cmd, t_list *env, t_list *paths)
{
    char   *new;
    struct stat	buf;

    while (paths)
    {
        new = ft_strjoin(paths->content, "/");
        new = ft_strjoin(new, cmd[0]);
        if (!stat(new, &buf))
            execve(new, cmd, ft_lst_toa(env));
        paths = paths->next;
    }
    if (!paths)
        miniprintf("Command not found: %s\n", cmd[0]);
    else
        execve(new, cmd, ft_lst_toa(env));
}

int ft_bin(char **cmd, t_list *env)
{
    t_list *paths;
    t_list *env_;

    env_ = env;
    while (env_)
    {
        if(!ft_strncmp(env_->content, "PATH=", 5))
        {
            paths = ft_lst_split(env_->content + 5, ":", 1);
            ft_find_bin(cmd, env, paths);
        }
        env_ = env_->next;
    }
    return (0);
}

char **ft_correct(char **cmd, t_list *lst)
{
    size_t  i;
    char    *tmp;
    char    **stmp;

    i = 0;
    while (cmd[i])
    {
        if (ft_containvarenv(cmd[i]))
            cmd[i] = ft_cleancmd(ft_lst_toa(ft_lst_split(cmd[i], "$", 0)), lst);
        i++;
    }
    return (cmd);
}

int     ft_exec(char **cmd, t_list **env)
{
    cmd = ft_correct(cmd, *env);
    if (!ft_strcmp(cmd[0], "echo"))
        return (ft_echo(cmd, *env));
    else if (!ft_strcmp(cmd[0], "pwd"))
        return (ft_pwd());
    else if (!ft_strcmp(cmd[0], "env"))
        return (ft_env(cmd, *env));
    else if (!ft_strcmp(cmd[0], "export"))
        return (ft_export(cmd, *env));
    else if (!ft_strcmp(cmd[0], "unset"))
        return (ft_unset(cmd, env));
    else if (!ft_strcmp(cmd[0], "exit"))
        return (ft_exit(cmd, *env));
    else
        return(ft_bin(cmd, *env));
}