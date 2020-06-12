#include "../includes/minishell.h"

t_list *ft_list_split(char *s, char c)
{
    t_list *lst;
    t_list *word;
    char *ptr;

    ptr = s;
    lst = NULL;
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == c)
        {
            if (ptr != s)
            {
                ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
            }
            ptr = (char *)s + 1;
        }
        s++;
    }
    if (ptr != s)
        ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
    return (lst);
}

void	ft_list_print(t_list *ptr, int flag)
{
	int	i = 0;

	if (ptr)
	{
		flag == 1 ? printf("[%d] : %s\n", i, (char *)ptr->content) :
		printf("%s\n",(char *) ptr->content);
		while(ptr->next)
		{
			ptr = ptr->next;
			i++;
			flag == 1 ? printf("[%d] : %s\n", i, (char *)ptr->content) :
			printf("%s\n", (char *)ptr->content);
		}
	}
}

int main(int ac, char **av)
{
    t_list *l;

    l = ft_list_split("bonjour je \";\" suis juliette", ';');
    ft_list_print(l, 1);
}