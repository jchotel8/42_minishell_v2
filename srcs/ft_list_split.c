#include "../includes/minishell.h"

t_list *ft_lst_split(char *s, char *c, int i)
{
    t_list *lst;
    char *ptr;
    char quote;
    char prev;

    lst = NULL;
    ptr = s;
    quote = 0;
    prev = 0;
    if (!s)
        return NULL;
    while (*s)
    {
        quote_inside(&quote, *s, prev);
        if (!quote && ft_strrchr(c, *s))
        {
            if (ptr != s)
            {
                ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
            }
            ptr = (char *)s + i;
        }
        prev = *s;
        s++;
    }
    if (ptr != s)
        ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
    return (lst);
}

void parse_redir(char *str, t_list **cmd, t_list **redirg, t_list **redird)
{
    t_list *tmp;
    t_list *tmp_cmd;

    tmp_cmd = NULL;
    tmp = ft_lst_split(str, "<>", 0);
    while (tmp)
    {
        if(!ft_strncmp(tmp->content, "<", 1))
            ft_lstadd_back(redirg, ft_lstnew(tmp->content));
        else if(!ft_strncmp(tmp->content, ">", 1))
            ft_lstadd_back(redird, ft_lstnew(tmp->content));
        else
            ft_lstadd_back(cmd, ft_lstnew(tmp->content));
        tmp = tmp->next;
    }
    //*cmd = ft_lst_split(tmp_cmd->content, " ", 1);
    // while (tmp_cmd)
    // {
        
    //     tmp_cmd = tmp_cmd->next;
    // }


}

int main(int ac, char **av)
{
    t_list *cmd;
    t_list *redirg;
    t_list *redird;
    
    redirg = NULL;
    redird = NULL;
    cmd = NULL;
    parse_redir("echo salut< test >>out bye", &cmd, &redirg, &redird);

    ft_putstr("CMD\n");
    ft_lst_print(cmd, 2);

    ft_putstr("REDIR G\n");
    ft_lst_print(redirg, 2);

    ft_putstr("REDIR D\n");
    ft_lst_print(redird, 2);

    ft_putstr("-------OBJECTIF-----------\n");
    ft_putstr("CMD\n");
    ft_putstr("\"echo\" \"salut\" \"bye\"\n");
    ft_putstr("REDIR G\n");
    ft_putstr("\"test\"\n");
    ft_putstr("REDIR D\n");
    ft_putstr("\"out\"\n");
}