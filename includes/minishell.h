/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:05:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <dirent.h>

# include "get_next_line.h"
# include "../libs/libft/libft.h"

# define RED "\033[0;0m\x1b[38;2;232;72;119m"
# define WHI "\x1b[38;2;255;235;202m"
# define YEL "\x1b[38;2;232;212;98m"

/*
**# define PROMPT  YEL "✦ "YEL "%s "RED"(%s) ➜ "WHI
**# define PROMPT_ RED "✦ "YEL "%s "RED"(%s) ➜ "WHI
*/
# define ERR_MSG_C "erreur de syntaxe près du symbole inattendu « %c »\n"
# define ERR_MSG_S "erreur de syntaxe près du symbole inattendu « %s »\n"

typedef struct	s_pipe
{
	char		**cmd;
	t_list		*redird;
	t_list		*redirg;
	t_list		*typed;
	t_list		*typeg;
}				t_pipe;

int				rep;

/*
** FT_PIPES
*/
void			do_pipe(t_list *line, int nb_cmd, t_list **env);
/*
** FT_QUOTES
*/
char			quote_inside(char *quote, char new, char prev);
char			*ft_strtrim_quote(char *s);
/*
** COMMANDES
*/
int				ft_echo(char **cmd, t_list *lst);
int				ft_pwd();
char			*get_wd();
int				ft_env(char **cmd, t_list **env);
int				ft_export(char **cmd, t_list **env);
int				ft_unset(char **cmd, t_list **env);
int				ft_exec(char **cmd, t_list **env);
int				ft_exec2(char **cmd, t_list **env);
int				ft_cd(char **cmd, t_list *env);
/*
** FT_PARSE
*/
int				parse_redir(char *str, t_pipe *pipe, t_list *env);
/*
** FT_LIST_SPLIT
*/
t_list			*ft_lst_split(char *s, char *c, int i);
/*
** EXIT
*/
int				ft_exit(char **cmd, t_list *env);
/*
** FT_REPLACE
*/
char			*ft_replace_env(char *str, t_list *env);
char			*ft_find_env(char *str, t_list *env);
/*
** FT_CHECKREAD
*/
int				ft_checkread(char *read);

/*
** utils_pipes
*/
void			init_pipes(int nb_pipes, int *pipes);
void			close_pipes(int nb_pipes, int *pipes);
void			wait_pipes(int nb_cmd, pid_t *pid, int *ret, int *pipes);
void			free_pipe(t_pipe *p);
void			set_pipe(t_pipe *p);
int				pipe_condi(int i, t_pipe *p, int nb_cmd);
void			start_pipe(int *flag, int *j, int nb_cmd, int *pipes);
/*
** utils_minishell
*/
int				ft_strstri(const char *s1, const char *s2);
char			*ft_strrep(char *str, char *to_rep, char *rep);
int				ft_isend(char c);
int				ft_isulsign(char c);
t_list			*ft_lstrep(t_list *prev, t_list *add, t_list *rep);

/*
** ***********BONUS*******************
** FT_WILDCARD
*/
char			*ft_rdirectory();
char			*ft_parsestrdir(char *str);

#endif
