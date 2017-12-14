/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:05:11 by amichak           #+#    #+#             */
/*   Updated: 2017/11/17 17:05:17 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t		i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

size_t ft_strlen_u(char *s)
{
	size_t i;
	int num;

	i = 0;
	if (s)
		while (*s || *(s + 1) || *(s + 2) || *(s + 3))
		{
			num = 0;
			num += (unsigned char) *s;
			num += ((int) ((unsigned char) *(s + 1))) << 8;
			num += ((int) ((unsigned char) *(s + 2))) << 16;
			num += ((int) ((unsigned char) *(s + 3))) << 24;
			if (num <= 127)
				i += 1;
			else if (num <= 2047)
				i += 2;
			else if (num <= 65535)
				i += 3;
			else if (num <= 2097151)
				i += 4;
			else
				break;
			s += 4;
		}
	return (i);
}
