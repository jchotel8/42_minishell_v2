#include "../includes/minishell.h"


//THINGS TO DO :
//- ft_exit : free when fail
//- free & cleanup
//- ctrl-C, ctrl-D, ctrl-/
//- redir of type 1 or 2
//- ajouter les quotes qd print export

void  sig_handler(int sig)
{
	rep = 130;
	if (sig == SIGINT)
  		miniprintf("\n"PROMPT_, "MINISHELL", get_wd());
	if (sig == SIGQUIT)
  		miniprintf("BONJOUR");
}

    // ctrl-D : ecriture  -> bloque : rien ne se passe
    // ctrl-D : prog      -> ne fait rien
    // ctrl-D : rien      -> exit bash (EOF->sur entree standard)
    // ctrl-C : ecriture  -> retour a la ligne (et ^C)
    // ctrl-C : prog      -> quitte le programme
    // ctrl-C : rien      -> retour a la ligne (et ^C)
    // ctrl-\ : ecriture  -> ?
    // ctrl-\ : prog      -> "Quitter (core dumped)"
    // ctrl-\ : rien      -> ?


int rep;

int     main(int ac, char **av, char **env)
{
	t_list  *lst_env;

	rep = 0;
	lst_env = ft_ato_lst(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (ac > 0)
	{
		char *read;
		t_list *line;
		t_list *pipe;
		miniprintf((rep == 0 ? PROMPT: PROMPT_), "MINISHELL", get_wd());
		while (get_next_line(0, &read)) 
		{	
			line = ft_lst_split(read, ";", 1);
			while(line)
			{
				pipe = ft_lst_split(line->content, "|", 1);
				do_pipe(pipe, ft_lstsize(pipe), &rep, &lst_env);
				line = line->next;
			}
			miniprintf((rep == 0 ? PROMPT: PROMPT_), "MINISHELL", get_wd());
		}
		miniprintf("exit\n");
	}
}

