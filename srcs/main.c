#include "../includes/minishell.h"


//THINGS TO DO :
//- ft_exit : free when fail
//- free & cleanup
//- ctrl-C, ctrl-D, ctrl-/
//- if one of my bin fails (unset ou export, env ?) in a pipe, check $?
//- redir of type 1 or 2
//- ajouter les quotes qd print export


int rep;

int     main(int ac, char **av, char **env)
{
	t_list  *lst_env;

	rep = 0;
	lst_env = ft_ato_lst(env);
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
		miniprintf("\nEXITING MINISHELL : \"%s\"\n", read);
	}
}

