/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:25:00 by amichak           #+#    #+#             */
/*   Updated: 2017/11/23 16:25:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     handle_umas(unsigned int *a, unsigned int c, int len)
{
    int             i;
    unsigned int    mask;
    int             offst;

    i = 0;
    offst = 0;
    mask = 255;
    while (i < 4)
        a[i++] = 0;
    i = len;
    while (i--)
    {
        a[i] = (c & mask) >> (8 * offst++);
        mask <<= 8;
    }
    i = 0;
    while (i < len)
        write(1, &a[i++], 1);
    return (len);
}

int ft_putchar_u(int c)
{
    unsigned int v2;
    unsigned int v3;
    unsigned int v4;
    unsigned int a[4];

    v2 = 49280;
    v3 = 14712960;
    v4 = 4034953344;
    if (c <= 127)
        return (handle_umas(a, c, 1));
    else if (c <= 2047)
        return (handle_umas(a, (((c & 63) | ((c & 1984) << 2)) | v2), 2));
    else if (c <= 65535)
        return (handle_umas(a, (((c & 63) | ((c & 4032) << 2) | \
                ((c & 61440) << 4)) | v3), 3));
    else if (c <= 2097151)
        return (handle_umas(a, (((c & 63) | ((c & 4032) << 2) | \
                ((c & 258048) << 4) | ((c & 1835008) << 6)) | v4), 4));
    return (0);
}
