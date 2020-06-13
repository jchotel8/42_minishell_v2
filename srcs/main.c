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
//     char *cmd[] = {
//         "pwd",
//         "Makefile",
//         NULL
//     };
//     do_exec(cmd);
// }


int main(int ac, char **av)
{
	int     rep;

	char *pipe1 = "grep p < Makefile";
	char *pipe2 = "head -n 10";
	char *pipe3 = "cut -b 1-10 > test";
	char *line[] = {pipe1, pipe2, pipe3};

	do_pipe(line, 3, &rep);
	printf("REP %d\n", rep);
}