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

#include "minishell.h"

int		is_redir_in(char *mot, t_list **t, t_list *p1, t_list *p2)
{
	if ((!ft_strncmp(mot, "<", 1) || (p1 && !ft_strlcmp(p1->content, "<")))
	&& ft_strlcmp(mot, "<"))
		ft_lstadd_back(t, ft_lstnew(
			ft_strdup((p2 && !ft_strlcmp(p2->content, "<") ? "2" : "1"))));
	return ((!ft_strncmp(mot, "<", 1) || (p1 && !ft_strlcmp(p1->content, "<")))
	&& ft_strlcmp(mot, "<"));
}

int		is_redir_out(char *mot, t_list **t, t_list *p1, t_list *p2)
{
	if ((!ft_strncmp(mot, ">", 1) || (p1 && !ft_strlcmp(p1->content, ">")))
	&& ft_strlcmp(mot, ">"))
	{
		if ((p2 && !ft_strlcmp(p2->content, ">") 
		&& p1 && !ft_strlcmp(p1->content, ">")) ||
		(p1 && !ft_strlcmp(p1->content, ">") && !ft_strncmp(mot, ">", 1)))
		{
			ft_lstadd_back(t, ft_lstnew(ft_strdup("2")));
		}
		else 
			ft_lstadd_back(t, ft_lstnew(ft_strdup("1")));
	}
	return ((!ft_strncmp(mot, ">", 1) || (p1 && !ft_strlcmp(p1->content, ">")))
	&& ft_strlcmp(mot, ">"));
}

void	sort_redir(char *str, t_pipe *p, t_list **cmd)
{
	t_list *r;
	t_list *start;
	t_list *p1;
	t_list *p2;

	set_pipe(p);
	r = ft_lst_split(str, "> <", 0);
	start = r;
	p1 = NULL;
	p2 = NULL;
	while (r)
	{
		if (is_redir_in(r->content, &p->typeg, p1, p2))
			ft_lstadd_back(&p->redirg, ft_lstnew(ft_strtrim(r->content, "< ")));
		else if (is_redir_out(r->content, &p->typed, p1, p2))
			ft_lstadd_back(&p->redird, ft_lstnew(ft_strtrim(r->content, "> ")));
		else if (ft_strlcmp(r->content, ">") && ft_strlcmp(r->content, "<")
		&& ft_strlcmp(r->content, " "))
			ft_lstadd_back(cmd, ft_lstnew(ft_strtrim(r->content, " ")));
		p2 = p1;
		p1 = r;
		r = r->next;
	}
	ft_lstclear(&start, *free);
}

int		parse_env(t_list **lst, t_list *env, int f)
{
	t_list	*tmp;
	t_list	*p1;
	char	*str;
	t_list	*in;

	p1 = NULL;
	tmp = *lst;
	while (tmp)
	{
		str = ft_strdup(tmp->content);
		tmp->content = ft_replace_env(tmp->content, env);
		if ((ft_lstsize((in = ft_lst_split(tmp->content, " ", 1))) != 1) && f)
		{
			miniprintf("Minishell : %s : redirection ambigue\n", str);
			free(str);
			ft_lstclear(&in, *free);
			return (1);
		}
		free(str);
		tmp = ft_lstrep(p1, in, tmp);
		!p1 ? *lst = tmp : 0;
		p1 = tmp;
		tmp = (tmp ? tmp->next : NULL);
	}
	return (0);
}

int		parse_redir(char *str, t_pipe *pipe, t_list *env)
{
	t_list *lst_cmd;

	lst_cmd = NULL;
	sort_redir(str, pipe, &lst_cmd);
	parse_env(&lst_cmd, env, 0);
	if (parse_env(&pipe->redird, env, 1))
	{
		ft_lstclear(&lst_cmd, *free);
		return (1);
	}
	if (parse_env(&pipe->redirg, env, 1))
	{
		ft_lstclear(&lst_cmd, *free);
		ft_lstclear(&pipe->redird, *free);
		return (1);
	}
	ft_lstiter2(lst_cmd, ft_strtrim_quote);
	ft_lstiter2(pipe->redirg, ft_strtrim_quote);
	ft_lstiter2(pipe->redird, ft_strtrim_quote);
	pipe->cmd = ft_lst_toa(lst_cmd);
	ft_lstclear(&lst_cmd, *free);
	return (0);
}
