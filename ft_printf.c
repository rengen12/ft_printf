#include "ft_printf.h"

size_t padding(t_fs *fs, int width, int prec, size_t wordlen)
{
    size_t i;

    i = 0;
    if ((fs->zero && prec) ||(fs->zero && fs->minus))
        fs->zero = 0;
    else if (!prec)
        prec = width - wordlen;
    while (width-- > prec - wordlen && !fs->minus)
        i += ft_putchar(' ');
    if (fs->ch != 'f')
        while (prec-- > wordlen)
            i += ft_putchar('0');
    return (i);
}

size_t padding_after(t_fs *fs, int width, int prec, int wordlen)
{
    size_t i;

    i = 0;
    while (wordlen-- > 0 && fs->minus && fs->ch != 'f')
        i += ft_putchar(' ');
    if (fs->ch == 'f')
        while (prec--)
            i += ft_putchar('0');//divis prec when float was printed
    return (i);
}

size_t print_ordsymb(const char **s)
{
    size_t  i;

    i = 0;
    while (**s != 0)
    {
        if (**s == '%')
           if (*++*s != '%')
               break ;
        ft_putchar_u(*(*s)++);
        i++;
    }
    return (i);
}


int     ft_wordlen(ssize_t var)
{
    int     i;

    i = 0;
    while (var)
    {
        var /= 10;
        i++;
    }
    return (i);
}

size_t print(t_fs *fs, ssize_t var)
{
    size_t  i;

    i = 0;
    if (fs->ch == 'c')
        i += ft_putchar((char)var);
    else if (fs->ch == 's')
        i += ft_putstr((char *)var);
    else if (fs->ch == 'C')
        i += ft_putchar_u((int)var);
    else if (fs->ch == 'S')
        i += ft_putstr_u((char *)var);
    else if (fs->ch == 'i' || fs->ch == 'd' || fs->ch == 'D')
    {
        i += padding(fs, fs->width, fs->precision, ft_wordlen(var));
        i += ft_putnbr(var, 0, fs);
    }
    else if (fs->ch == 'f')
    {
        i += padding(fs, fs->width, fs->precision, ft_wordlen((ssize_t)var));
        i += ft_putnbr(var, 0, fs);
        //endofwork
    }
    return (i);
}

size_t print_base(t_fs *fs, size_t var)
{
    size_t  i;
    char    *systemstr;
    char    *str;

    systemstr = NULL;
    if (fs->ch == 'X')
        systemstr = "0123456789ABCDEF";
    else if (fs->ch == 'x' || fs->ch == 'p')
        systemstr = "0123456789abcdef";
    else if (fs->ch == 'O' || fs->ch == 'o')
        systemstr = "01234567";
    else if (fs->ch == 'b')
        systemstr = "01";
    str = ft_convert_base(var, systemstr);
    i += padding(fs, fs->width, fs->precision, (ft_strlen(str));
    return (i);
}

size_t print_str_fs(t_fs *fs, va_list ap)
{
    size_t  i;

    i = 0;
    if (fs->ch == 'o' || fs->ch == 'O' || fs->ch == 'x' || fs->ch == 'X' || \
            fs->ch == 'u' || fs->ch == 'U' || fs->ch == 'p' || fs->ch == 'b')
        i += print_base(fs, va_arg(ap, size_t));
    else if (fs->ch == 'd' || fs->ch == 'D' || fs->ch == 's' || fs->ch == 'S' || \
            fs->ch == 'c' || fs->ch == 'C' || fs->ch == 'i' || fs->ch == 'f')
        i += print(fs, va_arg(ap, ssize_t));
    i += padding_after(fs, fs->width, fs->precision, (fs->width - i)); //??? mb v else if
    return (i);
}

int		ft_atoi_printf(const char **nptr_t)
{
    int				i;
    int				sign;
    unsigned long	r;
    const char      *nptr;

    nptr = *nptr_t;
    i = 0;
    r = 0;
    sign = 1;
    while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
        i++;
    if (nptr[i] == '+' || nptr[i] == '-')
        if (nptr[i++] == '-')
            sign = -1;
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        r = r * 10 + (nptr[i] - '0');
        i++;
    }
    if (r > 9223372036854775807 && sign == -1)
        return (0);
    if (r > 9223372036854775807)
        return (-1);
    *nptr_t = nptr + i;
    return ((int)r * sign);
}

void handle_flags(t_fs *fs, char ch)
{
    if (ch == '-')
        fs->minus = 1;
    else if (ch == '+')
        fs->plus = 1;
    else if (ch == '#')
        fs->sh = 1;
    else if (ch == ' ')
        fs->space = 1;
    else if (ch == '0')
        fs->zero = 1;
}

void handle_modif(t_fs *fs, char ch)
{
    /*if (**s == 'h')
        if (*++(*s++) == 'h')
            fs->hh = 1;
        else
            fs->h = 1;
    else if (**s == 'l')
        if (*++(*s++) == 'l')
            fs->ll = 1;
        else
            fs->l = 1;
    else if (*(*s++) == 'L')
        fs->bl = 1;*/
    if (ch == 'h')
        fs->h++;
    else if (ch == 'l')
        fs->l++;
    else if (ch == 'L')
        fs->bl++;
    else if (ch == 'z')
        fs->z++;
    else if (ch == 'j')
        fs->j++;
}

size_t handle_str_fs(va_list ap, const char **s, t_fs *fs)
{
    while (**s == '-' || **s == '+' || **s == '#' || **s == ' ' || **s == '0')
        handle_flags(fs, *(*s)++);
    if (**s >= '0' && **s <= '9')
        fs->width = ft_atoi_printf(s);
    if (**s == '.')
    {
        (*s)++;
        fs->precision = ft_atoi_printf(s);
        fs->precision = (fs->precision > 0) ? fs->precision : 0;
    }
    while (**s == 'h' || **s == 'l' || **s == 'L' || **s == 'j' || **s == 'z')
        handle_modif(fs, *(*s)++);
    if (!**s)
        exit(1);
    fs->ch = *(*s)++;
    return (print_str_fs(fs, ap));
}

size_t handstrform(va_list ap, const char *frmt, t_fs *fs)
{
    size_t  i;

    i = 0;
    while (*frmt)
    {
        i += print_ordsymb(&frmt);
        if (*frmt)
            i += handle_str_fs(ap, &frmt, fs);
    }
    return (i);
}

void init_flags(t_fs *fs)
{
    fs->ch = 0;
    fs->sh = 0;
    fs->zero = 0;
    fs->minus = 0;
    fs->plus = 0;
    fs->space = 0;
    fs->width = 0;
    fs->precision = 1;
    fs->h = 0;
    fs->l = 0;
    fs->j = 0;
    fs->z = 0;
    fs->bl = 0;
}

int ft_printf(const char *format, ...)
{
    size_t  i;
    va_list ap;
    t_fs    *fs;

    if (!format)
        return (0);
    va_start(ap, format);
    i = 0;
    if ((fs = (t_fs *)malloc(sizeof(t_fs))))
    {
        init_flags(fs);
        i = handstrform(ap, format, fs);
        ft_memdel((void **)&fs);
    }
    va_end(ap);
    return (i);
}