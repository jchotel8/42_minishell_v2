#include "../includes/minishell.h"

int     main(int ac, char **av, char **env)
{
    int     rep;
    if (ac > 0)
    {
        char *read;
        t_list *line;
        t_list *pipe;
        miniprintf(PROMPT, "MINISHELL", get_wd());
        while (get_next_line(0, &read)) 
        {	
            line = ft_lst_split(read, ";", 1);
            while(line)
            {
                pipe = ft_lst_split(line->content, "|", 1);
                do_pipe(pipe, ft_lstsize(pipe), &rep);
                line = line->next;
            }
            miniprintf(PROMPT, "MINISHELL", get_wd());
        }
        miniprintf("\nEXITING MINISHELL : \"%s\"\n", read);
    }
}