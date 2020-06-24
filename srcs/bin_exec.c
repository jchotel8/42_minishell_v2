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
    {
        miniprintf("Command not found: %s\n", cmd[0]);
        return (1);
    }
    else
        return(execve(new, cmd, ft_lst_toa(env)));
}

int ft_bin(char **cmd, t_list *env)
{
    t_list *paths;
    t_list *env_;
    int     ret;

    env_ = env;
    while (env_)
    {
        if(!ft_strlcmp("PATH=", env_->content))
        {
            paths = ft_lst_split(env_->content + 5, ":", 1);
            if ((ret = ft_find_bin(cmd, env, paths)))
                return(ret);
        }
        env_ = env_->next;
    }
    return (1);
}

int     ft_mybin(char **cmd, t_list **env)
{
    //cmd = ft_correct(cmd, *env);
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
        return(ft_exit(cmd, *env));
    else
        return (-1);
}

int     ft_exec(char **cmd, t_list **env)
{
    if (!ft_mybin(cmd, env))
        return (0);
    return (ft_bin(cmd, *env));
}

int     ft_exec2(char **cmd, t_list **env)
{//chaque fonction return 0, sauf dans le cas du ft_bin-> -1 si echec
    pid_t pid;

    if (!ft_mybin(cmd, env))
        return (0);
    if (!(pid = fork()))
        return(ft_bin(cmd, *env));
    return(0);
}