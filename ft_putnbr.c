/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:02:46 by amichak           #+#    #+#             */
/*   Updated: 2017/10/25 21:22:18 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t ft_putnbr_rec(ssize_t n, size_t i)
{
	if (n >= 10)
		i = ft_putnbr_rec(n / 10, i);
	i += ft_putchar((char)((n % 10) + '0'));
	return (i);
}

size_t	ft_putnbr(ssize_t n, t_fs *fs)
{
	size_t i;

	i = 0;
	if (n < 0)
	{
		i += ft_putchar('-');
        n = -n;
	}
    if (fs->ch == 'u')
        n = (unsigned)n;
	if (fs->l == 1)
		n = (long)n;
    if (!fs->l)
        n = (int)n;
	if (n > 0 && !fs->plus && fs->space)
		i += ft_putchar(' ');
	else if (n > 0 && fs->plus)
		i += ft_putchar('+');
	i += ft_putnbr_rec(n, i);
	return (i);
}
