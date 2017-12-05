/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:36:21 by amichak           #+#    #+#             */
/*   Updated: 2017/11/03 17:36:23 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		parse_convert_base(size_t nb, char *bt, size_t c, char *r)
{
	if (nb >= c)
		parse_convert_base(nb / c, bt, c, r);
	ft_strncat(r, &bt[nb % c], 1);
}

char			*ft_convert_base(size_t nb, char *base_to, t_fs *fs)
{
	char			*r;
	int				l;
	size_t	    	max;
	int				mem;

	max = 1;
	mem = 1;
	l = ft_strlen(base_to);
	while (max <= nb)
	{
		max *= l;
		mem++;
	}
    if (fs->sh)
        mem += 2;
	r = ft_strnew(mem);
    if (nb && fs->ch == 'x' && fs->sh)
        ft_strncat(r, "0x", 1);
    else if (nb && fs->ch == 'X' && fs->sh)
        ft_strncat(r, "0X", 1);
    else if (nb && (fs->ch == 'o' || fs->ch == 'O') && fs->sh)
        ft_strncat(r, "0", 1);
	parse_convert_base(nb, base_to, l, &(*r));
	return (r);
}
