/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:11:09 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdarg.h>

int	miniprintf(char *str, ...)
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

int	miniprinte(char *str, ...)
{
	va_list va;
	char	c;

	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			(*str == 'd') ? ft_putnbr_fd(va_arg(va, int), 2) : 0;
			(*str == 's') ? ft_putstr_fd(va_arg(va, char *), 2) : 0;
			if (*str == 'c')
			{
				c = va_arg(va, int);
				write(2, &c, 1);
			}
			(*str != 'c' && *str != 'd' && *str != 's') ? write(2, str, 1) : 0;
		}
		else
			write(2, str, 1);
		str++;
	}
	va_end(va);
	return (0);
}
