#include "header.h"

void    ft_putchar(char caract)
{
    write(1, &caract, 1);
}

void    ft_putstr(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        ft_putchar(str[i++]);
}

int main()
{
    char *stock;
    ft_putstr("MINISHELL : ");
    while (get_next_line(0, &stock)) 
    {
        printf("%s\n", stock);
        ft_putstr("MINISHELL :");
    }
}