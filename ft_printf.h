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

#define EOC          "\x1b[0m"

#define BLACK        "\x1b[30m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define BK_BLACK     "\x1b[40m"
#define BK_RED       "\x1b[41m"
#define BK_GREEN     "\x1b[42m"
#define BK_YELLOW    "\x1b[43m"
#define BK_BLUE      "\x1b[44m"
#define BK_MAGENTA   "\x1b[45m"
#define BK_CYAN      "\x1b[46m"
#define BK_WHITE     "\x1b[47m"

#define BOLD         "\x1b[1m"
#define ITALIC       "\x1b[3m"
#define UNDERLINE    "\x1b[4m"
#define BLINK        "\x1b[5m"
#define INVERTED     "\x1b[7m"
#define INVISIBLE    "\x1b[8m"

typedef struct s_fs
{
    /*character*/
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
int     ft_wordlen(ssize_t var);
void    usemodifu(t_fs *fs, size_t *valu);
void    usemodifs(t_fs *fs, ssize_t *vals);
size_t	ft_strlen_u(char *s);
int		ft_atoi_printf(const char **nptr);
char	*ft_strchr(const char *s, int c);

#endif
