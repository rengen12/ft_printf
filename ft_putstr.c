/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:59:23 by amichak           #+#    #+#             */
/*   Updated: 2017/10/25 21:02:21 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t ft_putstr(char const *s, t_fs *fs)
{
	size_t i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (fs->prec_exist && (size_t)fs->precision < i && fs->ch == 's')
		i = fs->precision;
	write(1, s, i);
	return (i);
}
