#include "../includes/minishell.h"

int     main(int ac, char **av, char **env)
{
    char *test = "\"bonjour\\\"toi\"";
    miniprintf("%s -> %s\n", test, ft_strtrim_quote(test));

    // int     rep;
    // t_list  *lst_env;

    // lst_env = ft_ato_lst(env);
    // if (ac > 0)
    // {
    //     char *read;
    //     t_list *line;
    //     t_list *pipe;
    //     miniprintf(PROMPT, "MINISHELL", get_wd());
    //     while (get_next_line(0, &read)) 
    //     {	
    //         line = ft_lst_split(read, ";", 1);
    //         while(line)
    //         {
    //             pipe = ft_lst_split(line->content, "|", 1);
    //             if (do_pipe(pipe, ft_lstsize(pipe), &rep, &lst_env))
    //             {
    //                 printf("EXIT\n");
    //                 exit(1);
    //                 return (1);
    //             }
    //             line = line->next;
    //         }
    //         miniprintf(PROMPT, "MINISHELL", get_wd());
    //     }
    //     miniprintf("\nEXITING MINISHELL : \"%s\"\n", read);
    // }
}

