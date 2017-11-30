/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:36:14 by amichak           #+#    #+#             */
/*   Updated: 2017/11/03 17:36:16 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			check_b(char *b, char *c)
{
	if (b && c)
		while (*c && *b && *c++ == *b++)
			if (*b == '\0')
				return (1);
	return (0);
}

int			ind(char c, const char *b)
{
	int				counter;

	counter = 0;
	while (*b && *b != c)
	{
		counter++;
		b++;
	}
	return (counter);
}

long long	atoi_parse(char *s, char *b, int cb)
{
	int				        sign;
	unsigned long long		r;

	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	sign = *s == '-';
	if ((r = 0) == 0 && (*s == '+' || *s == '-'))
		s++;
	while (ind(*s, b) < cb)
		r = r * cb + ind(*s++, b);
    if (r > 9223372036854775807)
        return (0);
	return ((long long)(sign ? -r : r));
}

long long			ft_atoi_base(char *s, char *b)
{
	int				cb;

	if (!s || !b)
		return (0);
	if (!check_b(b, "0123456789ABCDEF") && !check_b(b, "0123456789abcdef"))
		return (0);
	if ((cb = ft_strlen(b)) < 2)
		return (0);
	return (atoi_parse(s, b, cb));
}
