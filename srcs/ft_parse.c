/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_redir(t_list *p, t_list *p1, char *c)
{
	// if()
	// 	ft_lstadd_back(&p, ft_lstnew(ft_strdup("2")));
	// else
	// 	ft_lstadd_back(&p, ft_lstnew(ft_strdup("2")));
	return ((!ft_strncmp(p->content, c, 1) ||
	(p1 && !ft_strlcmp(p1->content, c))) &&
	ft_strlcmp(p->content, c));
}

void	sort_redir(char *str, t_pipe *p, t_list **cmd)
{
	t_list *r;
	t_list *start;
	t_list *p1;

	r = ft_lst_split(str, "> <", 0);
	start = r;
	p1 = NULL;
	while (r)
	{
		if (is_redir(r, p1, "<"))
			ft_lstadd_back(&p->redirg, ft_lstnew(ft_strtrim(r->content, "< ")));
		else if (is_redir(r, p1, ">"))
			ft_lstadd_back(&p->redird, ft_lstnew(ft_strtrim(r->content, "> ")));
		else if (ft_strlcmp(r->content, ">") && ft_strlcmp(r->content, "<") && ft_strlcmp(r->content, " "))
			ft_lstadd_back(cmd, ft_lstnew(ft_strtrim(r->content, " ")));
		p1 = r;
	 	r = r->next;
	}
	ft_lstclear(&start, *free); //il faut utiliser ft_lstclear(&r, *free) ici!!!
}

int		parse_env(t_list **lst, t_list *env, int flag)
{
	t_list *tmp;
	t_list *p1;
	char *str;

	p1 = NULL;
	tmp = *lst;
	while (tmp)
	{
		str = ft_strdup(tmp->content);
		tmp->content = ft_replace_env(tmp->content, env);
		t_list *test = ft_lst_split(tmp->content, " ", 1);
		if (flag && ft_lstsize(test) > 1)
		{
			miniprintf("Minishell : %s : redirection ambigue\n", str);
			free(str);
			// ERROR ft_lstclear(&test, *free);
			return (1);
		}
		if (p1 && test)
			p1->next = test;
		else if (test)
			*lst = test;
		ft_lstadd_back(&test, tmp->next);
		p1 = tmp;
		tmp = tmp->next;
		free(str);
		// ERROR ft_lstclear(&test, *free);
	}
	return (0);
}


int		parse_redir(char *str, t_pipe *pipe, t_list *env)
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
	 parse_env(&lst_cmd, env, 0);
	 if (parse_env(&pipe->redird, env, 1))
	 	return (1);
	 if (parse_env(&pipe->redirg, env, 1))
	 	return (1);
	 tmp = lst_cmd;
	 while (tmp)
	{
		tmp->content = ft_strtrim_quote(tmp->content);
		tmp = tmp->next;
	}
	pipe->cmd = ft_lst_toa(lst_cmd);
	ft_lstclear(&lst_cmd, *free);
	return (0);
}
