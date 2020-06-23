#include "../includes/minishell.h"


//THINGS TO DO :
//- apply ft_reverse_quotes
//- finish exit
//- clean $ -> dans le cas ou la variable n'existe pas
//- apply ft_strtrim_quote;
//- bin cd
//- $?


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

int        ft_isspecial(char c)  //a ajouter dans la libft
{
    return (c == '\\' || c == '\"');
}

char *ft_reverse_quote(char *s)
{
	int i;
	int j;
	char quote;
	char *new;

	i = 0;
	j = 0;
    quote = 0;
	new = ft_calloc(ft_strlen(s)* 2 + 2, sizeof(char));
    if (s[0] != '\"')
        new[j++] = '\"';
    if (s[0] == '\'')
        i++;
    if (s[0] == '\"' || s[0] == '\'')
        quote = s[0];
	while (s[i])
	{
        if (s[i] == '\\' && quote == '\"')
        {
            new[j++] = s[i++];
            new[j++] = (!ft_isspecial(s[i]) ? '\\' : s[i++]);
        }
        else if (ft_isspecial(s[i]) && quote == '\'')
        {
            new[j++] = (!ft_isspecial(s[i + 1]) || (s[i + 1] !='\\' && ft_isspecial(s[i + 1]))? '\\' : s[i++]);
            new[j++] = s[i++];
        }
        else if (s[i] == '\'' && quote == '\'')
            i++;
        else if (s[i] == '\\')
        {
            if (!ft_isspecial(s[i + 1]))
                i++;
            else
            {
                new[j++] = s[i++];
                new[j++] = s[i++];
            }
        }
        else
	        new[j++] = s[i++];
	}
    quote != '\"' ? new[j] = '\"' : 0;
	return (new);
}





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
            //miniprintf("%s -> %s\n", read, ft_reverse_quote(read));
            //miniprintf("%s -> %s\n", read, ft_replace_env(read, lst_env));
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

