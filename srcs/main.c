#include "../includes/minishell.h"

int     do_exec(char **cmd)
{
    if (cmd[0] == "echo")
    {
        ft_echo(cmd);
        return (1);
    }
    else if (cmd[0] == "pwd")
    {
        ft_pwd();
        return (1);
    }
    else if (execvp(cmd[0], cmd))
        return (1);
    return (0);
}

// int main(int ac, char **av)
// {
// 	int     rep;

// 	char *read = "grep p < Makefile | head -n 10 | cut -b 1-10 > test";
// 	t_list *pipe;
// 	pipe = ft_lst_split(read, "|", 1);
//     do_pipe(pipe, ft_lstsize(pipe), &rep);
//     printf("REP %d\n", rep);
// }

int     main(int ac, char **av, char **env)
{
    int     rep;
    if (ac > 0)
    {
        char *read;
        t_list *line;
        t_list *pipe;
        miniprintf(PROMPT, "MINISHELL", "workingDir");
        while (get_next_line(0, &read)) 
        {			
            line = ft_lst_split(read, ";", 1);
            while(line)
            {
                pipe = ft_lst_split(line->content, "|", 1);
                do_pipe(pipe, ft_lstsize(pipe), &rep);
                line = line->next;
            }
            miniprintf(PROMPT, "MINISHELL", "workingDir");
        }
        miniprintf("\nEXITING MINISHELL : \"%s\"\n", read);
    }
}