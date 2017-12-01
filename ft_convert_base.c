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

#include "libft.h"

int		check_b(char *b, char *c)
{
	if (b && c)
		while (*c && *b && *c++ == *b++)
			if (*b == '\0')
				return (1);
	return (0);
}

void		parse_convert_base(long long nb, char *bt, int c, char *r)
{
	int		sign;

	sign = 1;
	if (nb < 0)
	{
		nb *= -1;
		sign = -1;
	}
	if (sign == -1)
	{
		ft_strncat(r, "-", 1);
		sign = 1;
	}
	if (nb >= c)
		parse_convert_base(nb / c, bt, c, r);
	ft_strncat(r, &bt[nb % c], 1);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char			*r;
	long long		nb;
	int				l;
	long long		max;
	int				mem;

	if ((r = NULL) && (!nbr || !base_to || !base_from || (!check_b(base_to, \
        "0123456789ABCDEF") && !check_b(base_to, "0123456789abcdef"))))
		return (NULL);
	max = 1;
	mem = 1;
	l = ft_strlen(base_to);
	nb = ft_atoi_base(nbr, base_from);
	while (max <= nb)
	{
		max *= l;
		mem++;
	}
	r = (char *)malloc(sizeof(char) * (mem + 1));
	ft_bzero(r, mem + 1);
	parse_convert_base(nb, base_to, l, &(*r));
	return (r);
}
