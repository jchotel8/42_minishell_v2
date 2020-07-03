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

int		rep;

void	ft_prompt(void)
{
	char *dir;

	dir = get_wd();
	miniprintf((rep == 0 ? YEL "✦ "YEL "%s "RED"(%s) ➜ "WHI :
	RED "✦ "YEL "%s "RED"(%s) ➜ "WHI), "MINISHELL", dir);
	if (dir != NULL)
		free(dir);
}

/*
** SIGINT : ctrl-C
** SIGINT : ctrl-/
**	ctrl-D : ecriture  -> bloque : rien ne se passe
**  ctrl-D : prog      -> ne fait rien
**  ctrl-D : rien      -> exit bash (EOF->sur entree standard)
**  ctrl-C : ecriture  -> retour a la ligne (et ^C)
**  ctrl-C : prog      -> quitte le programme
**  ctrl-C : rien      -> retour a la ligne (et ^C)
**  ctrl-\ : ecriture  -> ?
**  ctrl-\ : prog      -> "Quitter (core dumped)"
**  ctrl-\ : rien      -> ?
*/

void	sig_handler(int sig)
{
	rep = 130;
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		ft_prompt();
	}
	if (sig == SIGQUIT)
		miniprintf("BONJOUR");
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
	char	*read;

	rep = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (ac > 0 && av[0])
	{
		lst_env = ft_ato_lst(env);
		ft_prompt();
		while (get_next_line(0, &read))
		{
			read = ft_checkquotes(read);
			if (ft_checkread(read))
				parse_read(read, &lst_env);
			ft_prompt();
		}
		ft_lstclear(&lst_env, *free);
		free(read);
		miniprintf("exit\n");
	}
}
