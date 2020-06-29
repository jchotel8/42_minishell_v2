# include "./libft.h"
# include <stdarg.h>
# include <stdio.h>

int miniprintf(char *str, ...)
{
	va_list va;
	char	c;

	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			(*str == 'd') ? ft_putnbr(va_arg(va, int)) : 0;
			(*str == 's') ? ft_putstr(va_arg(va, char *)) : 0;
			if (*str == 'c')
			{
				c = va_arg(va, int);
				write(1, &c, 1);
			}
			(*str != 'c' && *str != 'd' && *str != 's') ? write(1, str, 1) : 0;
		}
		else
			write(1, str, 1);
		str++;
	}
	va_end(va);
	return (0);
}