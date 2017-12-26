/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <amichak@marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:07:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/14 17:07:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

int ft_atoi_printf(const char **nptr)
{
	int i;
	unsigned long r;

	i = 0;
	r = 0;
	while (**nptr >= '0' && **nptr <= '9')
	{
		r = r * 10 + (*(*nptr)++ - '0');
		i++;
	}
	if (r > 9223372036854775807)
		return (0);
	return ((int)r);
}
