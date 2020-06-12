#include "../includes/minishell.h"

/*int main()
{
    char *stock;
    ft_printf("MINISHELL : ");
    while (get_next_line(0, &stock)) 
    {
        ft_printf("%s\n", stock);
        ft_printf("MINISHELL :");
    }
} */

int   main(int ac, char **av)
{
    int     rep;

 	//cat Makefile bonjour test | head -n 5
 	char *cmd1 = "cat Makefile";
 	char *cmd2 = "cut -b 1-10";
 	char *cmd3 = "cut -b 2-5";   
 	char *cmd4 = "head -n 3";

 	char *redird1[] = {NULL};
 	char *redird2[] = {NULL};
 	char *redird3[] = {NULL};
 	char *redird4[] = {"test", NULL};

 	char *redirg1[] = {NULL};
 	char *redirg2[] = {NULL};
 	char *redirg3[] = {NULL};
 	char *redirg4[] = {NULL};

 	char *cmd[] = {cmd1, cmd2, cmd3, cmd4};
 	char **redird[] = {redird1, redird2, redird3, redird4};
 	char **redirg[] = {redirg1, redirg2, redirg3, redirg4};
 	do_pipe(cmd, redird, redirg, 4, &rep);
 	printf("REP %d\n", rep);

     printf("%s CHECK OF TRIM : %s\n", "\\\"bonjour\\\"",ft_strtrim_quote("\\\"bonjour\\\""));
}