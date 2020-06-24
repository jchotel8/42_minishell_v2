#include "../includes/minishell.h"

// void parse_redir(char *str, t_pipe *pipe, t_list *env)
// {
//     t_list *tmp;
//     t_list *prev;
// 	t_list *lst_cmd;

//     prev = NULL;
// 	lst_cmd = NULL;
//     pipe->cmd = NULL;
//     pipe->redird = NULL;
//     pipe->redirg = NULL;
//     str = ft_replace_env(str, env);
//     tmp = ft_lst_split(str, "> <", 0);
//     while (tmp)
//     {   
//         if((!ft_strncmp(tmp->content, "<", 1) || (prev && !ft_strncmp(prev->content, "<", 2))) && ft_strncmp(tmp->content, "<", 2))
//             ft_lstadd_back(&pipe->redirg, ft_lstnew(ft_strtrim(tmp->content, "< ")));
//         else if((!ft_strncmp(tmp->content, ">", 1) || (prev && !ft_strncmp(prev->content, ">", 2))) && ft_strncmp(tmp->content, ">", 2))
//             ft_lstadd_back(&pipe->redird, ft_lstnew(ft_strtrim(tmp->content, "> ")));
//         else if (ft_strncmp(tmp->content, ">", 2) && ft_strncmp(tmp->content, "<", 2) && ft_strncmp(tmp->content, " ", 2))
//             ft_lstadd_back(&lst_cmd, ft_lstnew(ft_strtrim(tmp->content, " ")));
//         prev = tmp;
//         tmp = tmp->next;
//     }
//     tmp = lst_cmd;
//     while (tmp)
//     {
//         //tmp->content = ft_replace_env(tmp->content, env);
//         //tmp->content = ft_strtrim_quote(tmp->content); 
//         tmp = tmp->next;
//     }
//     miniprintf("CMD-----------\n");
//     ft_lst_print(lst_cmd, 1);
//     miniprintf("REDIRD-----------\n");
//     ft_lst_print(pipe->redird, 1);
//     if (lst_cmd && lst_cmd->content)
//         miniprintf("list not null\n");
// 	pipe->cmd = ft_lst_toa(lst_cmd);
// }

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
    tmp = ft_lst_split(str, "> <", 0);
    while (tmp)
    {   
        if((!ft_strncmp(tmp->content, "<", 1) || (prev && !ft_strlcmp(prev->content, "<"))) && ft_strlcmp(tmp->content, "<"))
            ft_lstadd_back(&pipe->redirg, ft_lstnew(ft_strtrim(tmp->content, "< ")));
        else if((!ft_strncmp(tmp->content, ">", 1) || (prev && !ft_strlcmp(prev->content, ">"))) && ft_strlcmp(tmp->content, ">"))
            ft_lstadd_back(&pipe->redird, ft_lstnew(ft_strtrim(tmp->content, "> ")));
        else if (ft_strlcmp(tmp->content, ">") && ft_strlcmp(tmp->content, "<") && ft_strlcmp(tmp->content, " "))
            ft_lstadd_back(&lst_cmd, ft_lstnew(ft_strtrim(tmp->content, " ")));
        prev = tmp;
        tmp = tmp->next;
    }
    tmp = lst_cmd;
    t_list *prev2 = 0;
    while (tmp)
    {
        tmp->content = ft_replace_env(tmp->content, env);
        t_list *test = ft_lst_split(tmp->content, " ", 1);
        if (prev2 && test)
            prev2->next = test;
        else if (test)
            lst_cmd = test;
        ft_lstadd_back(&test, tmp->next);
        prev2 = tmp;
        tmp = tmp->next;
    }
    pipe->cmd = ft_lst_toa(lst_cmd);
    int i = -1;
    while (pipe->cmd[++i])
        pipe->cmd[i] = ft_strtrim_quote(pipe->cmd[i]);
}

