#include "../includes/minishell.h"

t_list *ft_lst_split(char *s, char *c, int i)
{
	t_list *lst;
	char *ptr;
	char quote;
	char prev;

	lst = NULL;
	ptr = s;
	quote = 0;
	prev = 0;
	if (!s)
		return NULL;
	while (*s)
	{
		quote_inside(&quote, *s, prev);
		if (!quote && ft_strrchr(c, *s))
		{
			if (ptr != s)
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
			}
			ptr = (char *)s + i;
		}
		prev = *s;
		s++;
	}
	if (ptr != s)
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(ptr, 0, s - ptr)));
	return (lst);
}
