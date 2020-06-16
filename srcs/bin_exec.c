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


int     ft_exec(char **cmd, t_list *env)
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
    else
        return(ft_bin(cmd, env));
    return (0);
}