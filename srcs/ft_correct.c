#include "../includes/minishell.h"

char	*ft_find_env(char *str, t_list *env)
{
	str = ft_strjoin(str, "=");
	while (env)
	{
		if (!ft_strlcmp(str, env->content))
			return (ft_substr(env->content, ft_strlen(str), ft_strlen(env->content)));
		env = env->next;
	}
	return (0);
}

int		ft_strstri(const char *s1, const char *s2)
{
	size_t  size;   
	size_t  len;
	char    *hay;
	char    *needle;
	int     i;

	hay = (char *)s1;
	needle = (char *)s2;
	i = 0;
	len = ft_strlen(hay);
	size = ft_strlen(needle);
	while (*hay && len >= size)
	{
		if (ft_strncmp(hay, needle, size) == 0)
			return (i);
		hay++;
		len--;
		i++;
	}
	return (-1);
}

char	*ft_strrep(char *str, char *to_rep, char *rep)
{
	char *new; 

	while(ft_strstri(str, to_rep) >= 0)
	{      
		new = ft_substr(str, 0, ft_strstri(str, to_rep));
		new = ft_strjoin(new, rep);
		new = ft_strjoin(new, ft_substr(str, ft_strstri(str, to_rep) + ft_strlen(to_rep), ft_strlen(str)));
		str = new;
	}
	return (str);
}

int		ft_isend(char c)
{
	return (ft_isspace(c) || !c || c == '"' || c == '\'' || c == '$');
}

char	*ft_find_toreplace(char *str)
{
	char    quote;
	char    prev;
	char    *to_replace;
	int     k;

	quote = 0;
	prev = 0;
	k = 1;
	while (*str)
	{
		quote_inside(&quote, *str, prev);
		if (prev != '\\' && *str == '$' && quote != '\'')
		{
			while (!ft_isend(*(str + k)))
				k++;
			return (ft_substr(str, 0, k));
		}
		prev = *str;
		str++;
	}
	return(NULL);
}

char	*ft_replace_env(char *str, t_list *env)
{
	char *to_rep;

	//miniprintf("ft_replace env : %d\n", rep);
	rep = (rep == 256 ? 1 : rep); 	//cat ndir
	rep = (rep == 512 ? 2 : rep);	//ls ndir || grep ||
	rep = (rep == 8 ? 1 : rep);		//one of my bin fails
	// rep = (rep != 0 && rep != 2 && rep != 512 && rep != 1 && rep != 127 ? 1 : rep);
	while((to_rep = ft_find_toreplace(str)))
	{
		if (!ft_strcmp(to_rep, "$?"))
			str = ft_strrep(str, to_rep, ft_itoa(rep));
		else if (!ft_strcmp(to_rep, "$"))
			return (str);
		else
			str = ft_strrep(str, to_rep, ft_find_env(to_rep + 1, env));
	}
	return (str);
}
