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

int     ft_putchar_u(int c)
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

int     ft_putstr_u(char *s, t_fs *fs)
{
    size_t  i;
    int     c;
    size_t  ret;

    if (!s)
        return (0);
    i = 0;
    ret = 0;
    while (s[i * 4] || s[i * 4 + 1] || s[i * 4 + 2] || s[i * 4 + 3])
    {
        c = 0;
        c += (unsigned char)s[i * 4];
        c += ((int)((unsigned char)s[i * 4 + 1])) << 8;
        c += ((int)((unsigned char)s[i * 4 + 2])) << 16;
        c += ((int)((unsigned char)s[i * 4 + 3])) << 24;
        ret += ft_putchar_u(c);
        i++;
		(void)fs;
        //if (fs->prec_exist && (size_t)fs->precision <= ret && fs->ch == 'S')
          //  return (ret);
    }
    return (ret);
}

size_t charlen(char *s)
{
	int     c;

	c = 0;
	c += (unsigned char)s[0];
	c += ((int)((unsigned char)s[1])) << 8;
	c += ((int)((unsigned char)s[2])) << 16;
	c += ((int)((unsigned char)s[3])) << 24;
	if (c <= 127)
		return (1);
	else if (c <= 2047)
		return (2);
	else if (c <= 65535)
		return (3);
	else if (c <= 2097151)
		return (4);
	else
		return (0);
}

int     ft_putnstr_u(char *s, size_t len)
{
	size_t  i;
	int     c;
	size_t  ret;

	if (!s)
		return (0);
	i = 0;
	ret = 0;
	while ((s[i * 4] || s[i * 4 + 1] || s[i * 4 + 2] || s[i * 4 + 3]) && ret < len)
	{
		//if ((ret + charlen(s + i * 4)) > (size_t)fs->precision)
			//return (ret);
		c = 0;
		c += (unsigned char)s[i * 4];
		c += ((int)((unsigned char)s[i * 4 + 1])) << 8;
		c += ((int)((unsigned char)s[i * 4 + 2])) << 16;
		c += ((int)((unsigned char)s[i * 4 + 3])) << 24;
		ret += ft_putchar_u(c);
		i++;
	}
	return (ret);
}