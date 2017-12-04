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

#include "libft/libft.h"

void		parse_convert_base(size_t nb, char *bt, int c, char *r)
{
	if (nb >= c)
		parse_convert_base(nb / c, bt, c, r);
	ft_strncat(r, &bt[nb % c], 1);
}

char			*ft_convert_base(size_t nb, char *base_to)
{
	char			*r;
	int				l;
	long long		max;
	int				mem;

	if ((r = NULL) == NULL && !base_to)
		return (NULL);
	max = 1;
	mem = 1;
	l = ft_strlen(base_to);
	while (max <= nb)
	{
		max *= l;
		mem++;
	}
	r = ft_strnew(mem);
	parse_convert_base(nb, base_to, l, &(*r));
	return (r);
}
