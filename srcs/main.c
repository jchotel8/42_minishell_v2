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

// int     main()
// {
//     char *stock;
//     ft_printf("MINISHELL : ");
//     /*while (get_next_line(0, &stock)) 
//     {			
//         ft_printf("%s\n", ft_strtrim_quote(stock));
//         ft_printf("MINISHELL :");
//     } */
// }


int main(int ac, char **av)
{
	int     rep;

	char *read = "grep p < Makefile | head -n 10 | cut -b 1-10 > test";
	t_list *read_lst;
	read_lst = ft_lst_split(read, "|", 1);
    do_pipe(read_lst, 3, &rep);
    printf("REP %d\n", rep);
}