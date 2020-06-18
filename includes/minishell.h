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
int  		do_pipe(t_list *line, int nb_cmd, int *ret, t_list **env);
//FT_QUOTES
char        quote_inside(char *quote, char new, char prev);
char        *ft_strtrim_quote(char *s);
//COMMANDES
int     	ft_echo(char **cmd, t_list *lst);
int    		ft_pwd();
char 		*get_wd();
int 		ft_env (char **cmd, t_list *env);
int 		ft_export(char **cmd, t_list *env);
int     	ft_unset(char **cmd, t_list **env);
int     	ft_exec(char **cmd, t_list **env);
//FT_PARSE
void        parse_redir(char *str, t_pipe *pipe);
//FT_LIST_SPLIT
t_list      *ft_lst_split(char *s, char *c, int i);
//EXIT
int     	ft_exit(char **cmd, t_list *env);
//FT_CORRECT
char		**ft_correct(char **cmd, t_list *lst);
char		*ft_findvarenv(char *str, t_list *lst);
char    	*ft_strndup(char *str);
#endif
