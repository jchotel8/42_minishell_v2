#include "../includes/minishell.h"


//THINGS TO DO :
//- add " " when exporting
//- finish forks
//- verify redirection when only one
//- clean $
//- apply ft_strtrim_quote;
//- display the export list when no arguments


// var="bonjour\toi" -> "bonjour\\toi";
// var="bonjour\\toi" -> "bonjour\\toi";
// var="bonjour\"toi" -> "bonjour\"toi";
// var="bonjour\'toi" -> "bonjour\\'toi";
// var="bonjour'toi" -> "bonjour'toi";

// var=bonjour\toi -> "bonjourtoi";
// var=bonjour\\toi -> "bonjour\\toi";
// var=bonjour\"toi -> "bonjour\"toi";
// var=bonjour\'toi -> "bonjour'toi";
// var=bonjour\ toi -> "bonjour toi";
// var=bonjour"toi -> retour_ligne;

// var='bonjour\toi' -> "bonjour\\toi";
// var='bonjour\\toi' -> "bonjour\\\\toi";
// var='bonjour\"toi' -> "bonjour\\\"toi";
// var='bonjour"toi' -> "bonjour\"toi";
// var='bonjour\'toi' -> retour a la ligne;



// char *ft_reverse_quote(char *s)
// {
// 	int i;
// 	int j;
// 	char quote;
// 	char prev;
// 	char *new;

// 	i = 0;
// 	j = 0;
// 	prev = 0;
// 	new = ft_calloc(ft_strlen(s)* 2 + 2, sizeof(char));
// 	while (s[i])
// 	{
// 		if((quote_inside(&quote, s[i], prev)))
// 			prev = s[i++];
// 		if (!quote && s[i] == '\\' && prev != '\\')
// 		 	prev = s[i++];
// 		else if (quote == '"' && s[i] == '\\' && 
// 			((s[i + 1] == '\\' && prev != '\\')|| s[i + 1] == '"'))
// 			prev = s[i++];
// 		else
// 		{
// 			prev = 0;
// 			new[j++] = s[i++];
// 		}
// 	}
// 	return (new);
// }

int     main(int ac, char **av, char **env)
{
    int     rep;
    t_list  *lst_env;

    lst_env = ft_ato_lst(env);
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
                do_pipe(pipe, ft_lstsize(pipe), &rep, &lst_env);
                line = line->next;
            }
            miniprintf(PROMPT, "MINISHELL", get_wd());
        }
        miniprintf("\nEXITING MINISHELL : \"%s\"\n", read);
    }
}

