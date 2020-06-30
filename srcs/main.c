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

#include "../includes/minishell.h"

/*
** THINGS TO DO :
** - ft_exit : free when fail
** - ctrl-C, ctrl-D, ctrl-/
** - echo bonjour > "newline error"
*/

int		rep;

void    ft_prompt(void)
{
    char *dir;

    dir = get_wd();
    miniprintf((rep == 0 ? PROMPT : PROMPT_), "MINISHELL", dir);
	if (dir != NULL)
        free(dir);
}

void	sig_handler(int sig)
{
	rep = 130;
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		ft_prompt();
	}
	if (sig == SIGQUIT) //ctrl-/
		miniprintf("BONJOUR");
}

/*
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



int		ft_isulsign(char caract)
{
	if ((caract == '<' || caract == '>'))
		return (1);
	return (0);
}

int		ft_checkread(char *read)
{
	size_t	i;
	int		s;
	char	prev;
	char 	quote;

	s = 0;
	i = 0;
	while (read[i])
	{
		quote_inside(&quote, read[i], prev);
		while (!quote && read[i] == '<' || read[i] == '>')
		{
			s++;
			i++;
		}
		if (s > 2)
		{
			miniprintf("ERROR : %c\n", read[i]);
			return (0);
		}
		else if (s > 0) 
		{
			while (ft_isspace(read[i]))
				i++;
			if (ft_isulsign(read[i]) || read[i] == 0)
			{
				if (read[i] != 0)
					miniprintf("bash: erreur de syntaxe près du symbole inattendu « %c »\n", read[i]);
				else
					miniprintf("bash: erreur de syntaxe près du symbole inattendu « newline »\n");
				return (0);
			} 
			else
				s = 0;
		}	
		prev = read[i];
		i++;
	}
	return (1);
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
		do_pipe(pipe, ft_lstsize(pipe), &rep, env);
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
	char *tmp;

	rep = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (ac > 0)
	{
		lst_env = ft_ato_lst(env);
		ft_prompt();
		while (get_next_line(0, &read))
		{
			if (ft_checkread(read))
				parse_read(read, &lst_env);
			ft_prompt();
		}
		ft_lstfree(&lst_env);
		free(read);
		miniprintf("exit\n");
	}
}
