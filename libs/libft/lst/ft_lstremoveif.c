#include "../libft.h"

void	ft_lst_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*remove;
	t_list	*current;

	current = *begin_list;
	while (current && current->next)
	{
		if ((*cmp)(current->next->content, data_ref) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
		}
		current = current->next;
	}
	current = *begin_list;
	if (current && (*cmp)(current->content, data_ref) == 0)
	{
		*begin_list = current->next;
		free(current);
	}
}
