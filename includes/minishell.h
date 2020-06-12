#	ifndef HEADER_H
#	define HEADER_H

#	ifndef BUFFER_SIZE
#	define BUFFER_SIZE 32
#	endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

# include "get_next_line.h"
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/includes/printf.h"

void    do_pipe(char **cmd, char ***redird, char ***redirg, int nb_cmd, int *ret);
char    quote_inside(char *quote, char new, char prev);
char    *ft_strtrim_quote(char *s);
int     do_exec(char **cmd);
void    ft_echo(char **cmd);
void    ft_pwd();

#	endif
