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
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <inttypes.h>

typedef struct s_fs
{
    /*charecter*/
    char ch;
    int nf;

    /*flags*/
    int sh;
    int zero;
    int minus;
    int plus;
    int space;

    int width;
    int precision;
    int prec_exist;
    int starw;
    int starp;

    /*modificators*/
    int h;
    int l;
    int j;
    int z;
    int bl;

}           t_fs;

int     ft_printf (const char *format, ...);
int     ft_putchar_u(int c);
int     ft_putstr_u(char *s, t_fs *fs);
char	*ft_itoa(size_t n);
char	*ft_convert_base(size_t nb, char *base_to, t_fs *fs);
size_t	ft_putchar(char c);
size_t	ft_putstr(char const *s, t_fs *fs);
size_t	ft_strlen(const char *s);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
char	*ft_strncat(char *dest, const char *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_putnbr(ssize_t n, t_fs *fs);
void	ft_strdel(char **as);
char	*ft_strdup(const char *s);
void    ft_putendl(char const *s);
size_t  padding_afsign(t_fs *fs, int wordlen);
int     ft_wordlen(ssize_t var, t_fs *fs);

#endif
