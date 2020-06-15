#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "get_next_line.h"
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/includes/printf.h"

# define PROMPT "\x1b[38;2;232;212;98m✦ %s \033[0;0m\x1b[38;2;232;72;119m(%s) ➜  \x1b[38;2;255;235;202m"

typedef struct	s_pipe
{
	char		**cmd;
	t_list		*redird;
	t_list		*redirg;
}				t_pipe;


//FT_PIPE
void        do_pipe(t_list *list, int nb_cmd, int *ret);
//FT_QUOTES
char        quote_inside(char *quote, char new, char prev);
char        *ft_strtrim_quote(char *s);
//FT_COMMANDES
int         do_exec(char **cmd);
//FT_PARSE
void        parse_redir(char *str, t_pipe *pipe);
//FT_LIST_SPLIT
t_list      *ft_lst_split(char *s, char *c, int i);
//MINIPRINTF
void 		miniprintf(char *str, ...);

#endif
