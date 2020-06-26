#include "../includes/minishell.h"

int is_redir(t_list *p, t_list *p1, char *c)
{
	return ((!ft_strncmp(p->content, c, 1) || 
	(p1 && !ft_strlcmp(p1->content, c))) && 
	ft_strlcmp(p->content, c));
}

void sort_redir(char *str, t_pipe *p, t_list **cmd)
{
	t_list *r;
	t_list *start;
	t_list *p1;

	r = ft_lst_split(str, "> <", 0);
	start = r;
	p1 = NULL;
	while (r)
	{   
	 	if(is_redir(r, p1, "<"))
			ft_lstadd_back(&p->redirg, ft_lstnew(ft_strtrim(r->content, "< ")));
		else if(is_redir(r, p1, ">"))
			ft_lstadd_back(&p->redird, ft_lstnew(ft_strtrim(r->content, "> ")));
		else if (ft_strlcmp(r->content, ">") && ft_strlcmp(r->content, "<") && ft_strlcmp(r->content, " "))
			ft_lstadd_back(cmd, ft_lstnew(ft_strtrim(r->content, " ")));
		p1 = r;
	 	r = r->next;
	}
	//ft_lstclear(&start, *free);
}


int parse_redir(char *str, t_pipe *pipe, t_list *env)
{
	t_list *tmp;
	t_list *prev;
	t_list *lst_cmd;

	prev = NULL;
	lst_cmd = NULL;
	pipe->cmd = NULL;
	pipe->redird = NULL;
	pipe->redirg = NULL;
    //ERROR : ft_rdirectory(str);
	sort_redir(str, pipe, &lst_cmd);
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
	tmp = pipe->redird;
	prev2 = 0;
	while (tmp)
	{
		char *str = ft_strdup(tmp->content);
		tmp->content = ft_replace_env(tmp->content, env);
		t_list *test = ft_lst_split(tmp->content, " ", 1);
		if (ft_lstsize(test) > 1)
		{		
			miniprintf("Minishell : %s : redirection ambigue\n", str);
			return (1);
		}
		if (prev2 && test)
			prev2->next = test;
		else if (test)
			pipe->redird = test;
		ft_lstadd_back(&test, tmp->next);
		prev2 = tmp;
		tmp = tmp->next;
	}
	tmp = pipe->redirg;
	prev2 = 0;
	while (tmp)
	{
		char *str = ft_strdup(tmp->content);
		tmp->content = ft_replace_env(tmp->content, env);
		t_list *test = ft_lst_split(tmp->content, " ", 1);
		if (ft_lstsize(test) > 1)
		{		
			miniprintf("Minishell : %s : redirection ambigue\n", str);
			return (1);
		}
		if (prev2 && test)
			prev2->next = test;
		else if (test)
			pipe->redirg = test;
		ft_lstadd_back(&test, tmp->next);
		prev2 = tmp;
		tmp = tmp->next;
	}
	tmp = lst_cmd;
	while (tmp)
	{
		tmp->content = ft_strtrim_quote(tmp->content);
		tmp = tmp->next;
	}
	pipe->cmd = ft_lst_toa(lst_cmd);
	return (0);
}

