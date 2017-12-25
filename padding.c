/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <amichak@marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:39:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/20 12:39:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t padding(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	if ((fs->zero && fs->prec_exist && ft_strchr("oxXubdsSifpf", fs->ch)) || \
			(fs->zero && fs->minus))
		fs->zero = 0;
	else if (fs->zero)
		fs->precision = ((fs->plus) || (fs->nf && !fs->plus) || fs->space) ? fs->width - 1 : fs->width;
	while (fs->width > wordlen + (fs->nf || fs->plus) + fs->space && !fs->minus && !fs->zero &&
		   fs->precision + (fs->nf || fs->plus) + fs->space < fs->width)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	if ((fs->ch != 'f' && fs->ch != 'd' && fs->ch != '%') || (fs->ch == '%' && fs->zero))
		while (fs->precision > wordlen && (((fs->ch == 'c' || fs->ch == 'C') && \
				fs->zero) || (fs->ch != 'c' && fs->ch != 'C')))
		{
			i += ft_putchar('0');
			fs->precision--;
		}
	return (i);
}

size_t padding_after(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	while (fs->width > wordlen && fs->minus && fs->ch != 'f')
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	if (fs->ch == 'f')
		while (fs->precision > 0)
		{
			i += ft_putchar('0');
			fs->precision--;
		}
	return (i);
}

size_t padding_afsign(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	while (fs->precision > wordlen && fs->ch != 'f')
	{
		i += ft_putchar('0');
		fs->precision--;
	}
	return (i);
}

size_t padding_str(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	if (((fs->zero && fs->minus)) && fs->ch != 'S')
		fs->zero = 0;
	else if (fs->zero)
		fs->precision = fs->width;
	while (fs->width > wordlen && !fs->minus && !fs->zero)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	while (fs->precision > wordlen && fs->zero)
	{
		i += ft_putchar('0');
		fs->precision--;
	}
	return (i);
}