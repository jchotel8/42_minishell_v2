#include "../includes/minishell.h"

int ft_env (char **cmd, t_list *env)
{   //env /home : erreur 126 denied acces
    if (cmd && cmd[1])
    {
        miniprintf("env: \"%s\": Aucun fichier ou dossier de ce type\n", cmd[1]);
        return (127);
    }
    ft_lst_print(env, 0);
    return (0);
}

// int ft_unset(char **cmd, t_list *env)
// {

// }

char	check_export(char *s)
{
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '-'))
			return (*s);
		s++;
	}
	return (*s);
}

int ft_export(char **cmd, t_list *env)
{
    int     i;
    char    c;

    i = 1;
    if (cmd && cmd[i])
    {
        while(cmd[i])
        {
            if (!(c = check_export(cmd[i])))
                ft_lstadd_back(&env, ft_lstnew(cmd[i++]));
            else
            {
                miniprintf("export: '%s': not a valid identifier\n", cmd[i]);
                return (1);
            }
        }
    }
    else
    {
        miniprintf("need to print the list (and sort)\n");
    }
    return (0);
}

void	ft_lstunset(t_list **lst, char *str)
{

    t_list  *new;
    t_list  *before;

	if (!lst)
		return ;
    new = *lst;
	while (new->next && new)
	{
        if (!ft_strncmp(ft_strjoin(str, "="), new->next->content, ft_strlen(ft_strjoin(str, "="))))
		{
            before = new->next;
            new->next = new->next->next;
            free(before);
        }
        printf("%s\n", new->content);
        new = new->next;
	}
    new = *lst;
    if (new)
    {
        *lst = new->next;
	    free(new);
    }
}

void    ft_clean(char *cmd, t_list *env)
{

}

int     ft_unset(char **cmd, t_list *env)
{
        size_t i;

        i = 1;
        while (cmd[i])
            ft_lstunset(&env, cmd[i++]);
        return (1);
}