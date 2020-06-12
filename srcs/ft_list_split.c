#include "../includes/minishell.h"

t_list *ft_list_split(char *s, char c)
{
    t_list *lst;
    char *ptr;

    ptr = 0;
    if (!s )
    
    while (*s)
    {
        if (*s == c)
        {
            if (ptr != s)
                ft_listadd_back(lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
            ptr = (char *)s + 1;
        }
        s++;
    }
    if (ptr != s)
        ft_listadd_back(lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
    //lst = ft_listadd_front(ft_lstnew(strdup)
    return (*lst);
}

void	ft_list_print(t_list *ptr, int flag)
{
	int	i = 0;

	if (ptr)
	{
		flag == 1 ? printf("[%d] : %s\n", i, ptr->content) :
		printf("%s\n", ptr->content);
		while(ptr->next)
		{
			ptr = ptr->next;
			i++;
			flag == 1 ? printf("[%d] : %s\n", i, ptr->content) :
			printf("%s\n", ptr->content);
		}
	}
}

int main(int ac, char **av)
{
    t_list *l;

    l = ft_list_split("bonjour je suis juliette");
    
}