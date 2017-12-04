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
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

int     ft_printf (const char *format, ...);
int     ft_putchar_u(int c);
int     ft_putstr_u(char *s);
char	*ft_itoa(size_t n);
char	*ft_convert_base(size_t nb, char *base_to);
size_t	ft_putchar(char c);
size_t	ft_putstr(char const *s);
size_t	ft_strlen(const char *s);

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
    int h;
    int l;
    int j;
    int z;
    int bl;
}           t_fs;
#endif
