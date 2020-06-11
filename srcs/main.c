#include "header.h"

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