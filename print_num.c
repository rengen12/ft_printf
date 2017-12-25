/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <amichak@marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:40:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/20 12:40:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t print_num(t_fs *fs, va_list ap)
{
	ssize_t	var;
	size_t	i;

	i = 0;
	var = va_arg(ap, ssize_t);
	usemodifs(fs, &var);
	if (var < 0)
		fs->nf = 1;
	if (!fs->prec && !var)
		i += padding(fs, 0);
	else
	{
		i += padding(fs, ft_wordlen(var));
		i += ft_putnbr_prntf(var, fs);
	}
	return (i);
}

size_t print_unsig(t_fs *fs, va_list ap)
{
	size_t	i;
	char	*systemstr;
	char	*str;
	size_t	var;

	i = 0;
	var = va_arg(ap, size_t);
	usemodifu(fs, &var);
	i += handle_sharp(var, fs);
	if ((systemstr = NULL) == NULL && fs->ch == 'u')
		systemstr = "0123456789";
	else if (fs->ch == 'X')
		systemstr = "0123456789ABCDEF";
	else if (fs->ch == 'x' || fs->ch == 'p')
		systemstr = "0123456789abcdef";
	else if (fs->ch == 'o')
		systemstr = "01234567";
	else if (fs->ch == 'b')
		systemstr = "01";
	str = ft_convert_base(var, systemstr, fs);
	i += padding(fs, ft_strlen(str) + i);
	i += ft_putstr(str, fs);
	ft_strdel(&str);
	return (i);
}

size_t print_float(t_fs *fs, va_list ap)
{
	size_t		i;
	long double var;
	size_t 		i_e;

	i = 0;
	i_e = 0;
	if (fs->l)
		var = va_arg(ap, long double);//dont work with big num
	else
		var = va_arg(ap, double);
	if (var < 0)
	{
		var *= -1;
		fs->nf = 1;
	}
	if (fs->prec == -1)
		fs->prec = 6;
	if (fs->ch == 'e' || fs->ch == 'E')
		while ((size_t)var >= 10)
		{
			i_e++;
			var /= 10;
		}
	i += padding(fs, (ft_wordlen((size_t)var) + (fs->prec > 0) + fs->prec));
	i += ft_putnbr_prntf((size_t)var, fs);
	fs->nf = 0;
	if (fs->prec > 0)
		i += ft_putchar('.');
	while (fs->prec-- > 0)
	{
		var -= (size_t)var;
		//var += 0.000000000001;
		var *= 10;
		if ((fs->prec == 0) && ((size_t)(var * 10) % 10) >= 5)
			var++;
		i += ft_putnbr_prntf((size_t)var, fs);
	}
	if (fs->ch == 'e' || fs->ch == 'E')
	{
		i += ft_putchar(fs->ch);
		i += ft_putchar('+');
		if (i_e >= 10)
			i += ft_putnbr_prntf(i_e, fs);
		else
		{
			i += ft_putnbr_prntf(0, fs);
			i += ft_putnbr_prntf(i_e, fs);
		}
	}
	return (i);
}
