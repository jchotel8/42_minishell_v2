#include "../includes/minishell.h"


//THINGS TO DO :
//- $ with > or |
//- ft_exit : free when fail
//- free & cleanup
//- $? a finir : si une commande n'est pas trouvée et les valeurs != 0
//- ctrl-C, ctrl-D, ctrl-/
//- bin -> path absolu
//- export ou env : l'un n'affiche pas si pas de value
//- apres un "export" les variables d'env ne doivent pas etre triées
//- tester un dollard tout seul pour voir

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
                //miniprintf("return value = %d\n", rep);
                line = line->next;
            }
            miniprintf((rep == 0 ? PROMPT: PROMPT_), "MINISHELL", get_wd());
        }
        miniprintf("\nEXITING MINISHELL : \"%s\"\n", read);
    }
}

