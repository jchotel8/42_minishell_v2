#include "../includes/minishell.h"

char *ft_rdirectory(char *str)
{
    struct dirent   *var;
    char            *tmp;
    char            *array;
    DIR             *dir;

    dir = opendir(".");
    while ((var = readdir(dir)))
    {
        tmp = ft_strdup(var->d_name);
        array = ft_strjoin(array, tmp);
    }
    closedir(dir);
    return (tmp);
}