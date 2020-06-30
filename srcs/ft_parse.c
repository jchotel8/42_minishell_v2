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

int		is_redir(char *mot, t_list **t, t_list *p1, t_list *p2, char *c)
{
	if ((!ft_strncmp(mot, c, 1) || (p1 && !ft_strlcmp(p1->content, c))) && ft_strlcmp(mot, c))
		ft_lstadd_back(t, ft_lstnew(ft_strdup((p2 && !ft_strlcmp(p2->content, c)? "2" : "1"))));
	return ((!ft_strncmp(mot, c, 1) || (p1 && !ft_strlcmp(p1->content, c))) && ft_strlcmp(mot, c));
} 
// si le mot est different de ">"
// &&
// si le mot commence par ">" || si le mot precedent est ">"

// alors
// si le mot precedent 2 est > 
// -> 2
// sinon 1

void	sort_redir(char *str, t_pipe *p, t_list **cmd)
{
	t_list *r;
	t_list *start;
	t_list *p1;
	t_list *p2;

	r = ft_lst_split(str, "> <", 0);
	start = r;
	p1 = NULL;
	p2 = NULL;
	while (r)
	{
		if (is_redir(r->content, &p->typeg, p1, p2, "<"))
			ft_lstadd_back(&p->redirg, ft_lstnew(ft_strtrim(r->content, "< ")));
		else if (is_redir(r->content, &p->typed, p1, p2, ">"))
			ft_lstadd_back(&p->redird, ft_lstnew(ft_strtrim(r->content, "> ")));
		else if (ft_strlcmp(r->content, ">") && ft_strlcmp(r->content, "<") && ft_strlcmp(r->content, " "))
			ft_lstadd_back(cmd, ft_lstnew(ft_strtrim(r->content, " ")));
		p2 = p1;
		p1 = r;
	 	r = r->next;
	}
	ft_lstclear(&start, *free);
}

t_list *ft_lstrep(t_list *prev, t_list *add, t_list *rep)
{
    t_list *next;
	next = rep->next;
	free(rep->content);
	free(rep);
	if (add)
	{
		if (prev)
			prev->next = add;
		ft_lstadd_back(&add, next);
		return (add);
	}
	if (prev)
		prev->next = next;
	return (next);
}

int		parse_env(t_list **lst, t_list *env, int flag)
{
	t_list *tmp;
	t_list *p1;
	char *str;
	t_list *insert;

	p1 = NULL;
	tmp = *lst;
	while (tmp)
	{
		str = tmp->content;
		tmp->content = ft_replace_env(tmp->content, env);
		insert = ft_lst_split(tmp->content, " ", 1);
		if (flag && ft_lstsize(insert) > 1)
		{
			miniprintf("Minishell : %s : redirection ambigue\n", str);
			return (1);
		}
		tmp = ft_lstrep(p1, insert, tmp);
		if (!p1)
			*lst = tmp;
		p1 = tmp;
		tmp = (tmp ? tmp->next : NULL);
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
	pipe->typed = NULL;
	pipe->typeg = NULL;
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
