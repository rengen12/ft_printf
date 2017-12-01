/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:05:00 by amichak           #+#    #+#             */
/*   Updated: 2017/11/22 15:05:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

int     ft_printf (const char *format, ...);
int     ft_putchar_u(int c);
int     ft_putstr_u(char *s);

typedef struct s_fs
{
    /*int s;
    int S;
    int p;
    int d;
    int D;
    int i;
    int o;
    int O;
    int u;
    int U;
    int x;
    int X;
    int c;
    int C;*/
    /*charecter*/
    char ch;

    /*flags*/
    int sh;
    int zero;
    int minus;
    int plus;
    int space;

    int width;
    int precision;

    /*modificators*/
    int hh;
    int h;
    int l;
    int ll;
    int j;
    int z;
}           t_fs;
#endif
