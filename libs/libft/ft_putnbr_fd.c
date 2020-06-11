/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:31:24 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	val;

	val = (long int)n;
	if (val < 0)
	{
		ft_putchar_fd('-', fd);
		val = -val;
	}
	if (val > 9)
	{
		ft_putnbr_fd(val / 10, fd);
		ft_putchar_fd((val % 10) + '0', fd);
	}
	else
		ft_putchar_fd(val + '0', fd);
}
