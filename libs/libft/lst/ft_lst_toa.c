/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_toa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:18:24 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_lst_toa(t_list *lst)
{
	char	**new;
	int		i;

	if (!lst)
		return (NULL);
	if (!(new = (char **)malloc(sizeof(char *) * ft_lstsize(lst) + 1)))
		return(NULL);

	i = 0;
	while (lst)
	{
		if (ft_strlcmp(lst->content,""))
		{
			new[i] = ft_strdup((char *)lst->content);
			i++;
		}
		lst = lst->next;
	}
	new[i] = 0;
	return (new);
}