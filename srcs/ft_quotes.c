#include "../includes/minishell.h"

char	quote_inside(char *quote, char new, char prev)
{
	if (!*quote && prev != '\\' && (new == '\'' || new  == '"'))
	{
		*quote = new;
		return (1);
	}
	else if ((new == '\'' || (new  == '"' && prev != '\\')) && *quote == new)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

char	*ft_strtrim_quote(char *s)
{
	int		i;
	int		j;
	char	quote;
	char	prev;
	char	*new;

	i = 0;
	j = 0;
	prev = 0;
	new = ft_calloc(ft_strlen(s), sizeof(char));
	while (s[i])
	{
		if ((quote_inside(&quote, s[i], prev)))
			prev = s[i++];
		if (!quote && s[i] == '\\' && prev != '\\')
			prev = s[i++];
		else if (quote == '"' && s[i] == '\\' &&
				((s[i + 1] == '\\' && prev != '\\') || s[i + 1] == '"'))
			prev = s[i++];
		else if (prev == '"' && s[i] == '"')
			prev = s[i++];
		else
		{
			prev = 0;
			new[j++] = s[i++];
		}
	}
	return (new);
}
