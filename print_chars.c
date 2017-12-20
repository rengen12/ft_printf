/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <amichak@marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:38:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/20 12:38:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t print_string(t_fs *fs, va_list ap)
{
	size_t i;
	char *str;
	size_t l;

	i = 0;
	str = va_arg(ap, char *);
	if (fs->ch == 'S' || (fs->ch == 's' && fs->l))
		l = ft_strlen_u(str, fs);
	else
		l = ft_strlen(str);
	if (!str)
		l = 6;
	l = (l > (size_t)fs->precision && fs->prec_exist) ? (size_t)fs->precision : l;
	i += padding_str(fs, l);
	if (!str)
		i += ft_putstr("(null)", fs);
	else if (fs->ch == 's' && fs->l == 0)
		i += ft_putstr(str, fs);
	else if (fs->ch == 'S' || (fs->ch == 's' && fs->l))
		i += ft_putnstr_u(str, l);
	return (i);
}

size_t print_char(t_fs *fs, va_list ap)
{
	size_t	i;
	char	*var;

	i = 0;
	i += padding(fs, 1);
	if (fs->ch == '%')
		i += ft_putchar('%');
	else
		var = va_arg(ap, char *);
	if(fs->ch != '%')
	{
		if (fs->ch == 'c' && fs->l == 0)
			i += ft_putchar(*var);
		else if (fs->ch == 'C' || (fs->ch == 'c' && fs->l))
			i += ft_putnstr_u(var, 4);
	}
	return (i);
}