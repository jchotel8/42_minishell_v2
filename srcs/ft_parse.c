#include "../includes/minishell.h"

void parse_redir(char *str, t_pipe *pipe, t_list *env)
{
    t_list *tmp;
    t_list *prev;
	t_list *lst_cmd;

    prev = NULL;
	lst_cmd = NULL;
    pipe->cmd = NULL;
    pipe->redird = NULL;
    pipe->redirg = NULL;
    str = ft_replace_env(str, env);
    tmp = ft_lst_split(str, "> <", 0);
    while (tmp)
    {   
        if((!ft_strncmp(tmp->content, "<", 1) || (prev && !ft_strncmp(prev->content, "<", 2))) && ft_strncmp(tmp->content, "<", 2))
            ft_lstadd_back(&pipe->redirg, ft_lstnew(ft_strtrim(tmp->content, "< ")));
        else if((!ft_strncmp(tmp->content, ">", 1) || (prev && !ft_strncmp(prev->content, ">", 2))) && ft_strncmp(tmp->content, ">", 2))
            ft_lstadd_back(&pipe->redird, ft_lstnew(ft_strtrim(tmp->content, "> ")));
        else if (ft_strncmp(tmp->content, ">", 2) && ft_strncmp(tmp->content, "<", 2) && ft_strncmp(tmp->content, " ", 2))
            ft_lstadd_back(&lst_cmd, ft_lstnew(ft_strtrim(tmp->content, " ")));
        prev = tmp;
        tmp = tmp->next;
    }
	pipe->cmd = ft_lst_toa(lst_cmd);
}
