/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** THINGS TO DO :
** - ctrl-C, ctrl-D, ctrl-/
*/

int		g_rep;
char	*g_read;

void	ft_prompt(void)
{
	char *dir;

	dir = get_wd();
	if (g_rep != 2)
		miniprintf((g_rep == 0 ? YEL "✦ "YEL "%s "RED"(%s) ➜ "WHI :
		RED "✦ "YEL "%s "RED"(%s) ➜ "WHI), "MINISHELL", dir);
	if (dir != NULL)
		free(dir);
}

/*
** SIGINT : ctrl-C
** SIGQUIT : ctrl-/
**	ctrl-D : ecriture  -> bloque : rien ne se passe
**  ctrl-D : prog      -> ne fait rien
**  ctrl-D : rien      -> exit bash (EOF->sur entree standard)
**  ctrl-C : ecriture  -> retour a la ligne (et ^C)
**  ctrl-C : prog      -> quitte le programme
**  ctrl-C : rien      -> retour a la ligne (et ^C)
**  ctrl-\ : ecriture  -> rien
**  ctrl-\ : prog      -> "Quitter (core dumped)"
**  ctrl-\ : rien      -> rien
*/

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		g_rep = 130;
		ft_prompt();
	}
	if (sig == SIGQUIT && (!g_read || (g_read
	&& ft_strlen(g_read) == 0)))
		miniprintf("\b\b  \b\b");
	else if (sig == SIGQUIT && g_read && ft_strlen(g_read) > 0)
	{
		kill(1, SIGINT);
		miniprintf("Quitter (core dumped) [%s]\n", g_read);
	}
}

void	parse_read(char *read, t_list **env)
{
	t_list *line;
	t_list *pipe;
	t_list *start;

	line = ft_lst_split(read, ";", 1);
	start = line;
	while (line)
	{
		pipe = ft_lst_split(line->content, "|", 1);
		do_pipe(pipe, ft_lstsize(pipe), env);
		ft_lstclear(&pipe, *free);
		line = line->next;
	}
	ft_lstclear(&start, *free);
	free(read);
}

int		main(int ac, char **av, char **env)
{
	t_list	*lst_env;

	g_rep = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (ac > 0 && av[0])
	{
		lst_env = ft_ato_lst(env);
		handle_shlvl(&lst_env);
		ft_prompt();
		while (1)
			if (get_next_line(0, &g_read) == 1)
			{
				if (ft_checkread(g_read))
					parse_read(g_read, &lst_env);
				ft_prompt();
			}
			else if (ft_strlen(g_read) == 0)
				break ;
			else
				free(g_read);
		ft_lstclear(&lst_env, *free);
		free(g_read);
		miniprintf("exit\n");
	}
}
