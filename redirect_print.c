/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <amichak@marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:47:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/20 12:47:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t print_ordsymb(const char **s)
{
	size_t	i;

	i = 0;
	while (**s)
	{
		if (**s == '{')
			parse_color(s);
		if (**s == '%')
		{
			if (**s == '%')
				(*s)++;
			break;
		}
		if (**s)
			i += ft_putchar(*(*s)++);
	}
	return (i);
}

size_t print_str_fs(t_fs *fs, va_list ap)
{
	size_t i;

	if ((i = 0) == 0 && ft_strchr("oxXubdsScCifpf", fs->ch)) //remove %
	{
		if (fs->ch == 'f')
			i += print_float(fs, ap);
		else if (fs->ch == 's' || fs->ch == 'S')
			i += print_string(fs, ap);
		else if (fs->precision == -1)
			fs->precision = 1;
		if (ft_strchr("oxXubp", fs->ch))
			i += print_unsig(fs, ap);
		else if (fs->ch == 'd')
			i += print_num(fs, ap);
		else if (fs->ch == 'c' || fs->ch == 'C'/* || fs->ch == '%'*/)
			i += print_char(fs, ap);
		i += padding_after(fs, i);
	}
	else
	{
		i += padding(fs, 1);
		i += ft_putchar(fs->ch);
		i += padding_after(fs, i);
	}
	return (i);
}
