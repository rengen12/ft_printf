#include "ft_printf.h"

void usemodif(t_fs *fs, ssize_t *vals, size_t *valu)
{
    if (fs->h && *valu)
        if (fs->h == 1)
            *valu = (unsigned short int)*valu;
        else
            *valu = (unsigned char)*valu;
    else if (fs->h && *vals)
        if (fs->h == 1)
            *vals = (short int)*vals;
        else
            *vals = (char)*vals;
    else if (fs->l && *valu)
        if (fs->l == 1)
            *valu = (unsigned long int)*valu;
        else
            *valu = (unsigned long long int)*valu;
    else if (fs->l && *vals)
        if (fs->l == 1)
            *vals = (long int)*vals;
        else
            *vals = (long long int)*vals;
    else if (fs->bl)
        *vals = (long double)*vals;
    else if (fs->j && *vals)
        *vals = (intmax_t)*vals;
    else if (fs->j && *valu)
        *valu = (uintmax_t)*valu;
}

size_t padding(t_fs *fs, int wordlen)
{
    size_t i;

    i = 0;
    /*if (!fs->ch)
        while (fs->width--)
            i += ft_putchar(' ');*/
    if ((fs->zero && fs->precision) ||(fs->zero && fs->minus))
        fs->zero = 0;
    else if (fs->zero)
        fs->precision = fs->width - wordlen;
    while (fs->width > /*fs->precision - */wordlen && !fs->minus)
    {
        i += ft_putchar(' ');
        fs->width--;
    }
    if (fs->ch != 'f')
        while (fs->precision > wordlen)
        {
            i += ft_putchar('0');
            fs->precision--;
        }
    return (i);
}

size_t padding_after(t_fs *fs, int wordlen)
{
    size_t i;

    i = 0;
    while (fs->width > /*fs->precision - */wordlen && fs->minus && fs->ch != 'f')
    {
        i += ft_putchar(' ');
        fs->width--;
    }
    if (fs->ch == 'f')
        while (fs->precision)
        {
            i += ft_putchar('0');//divis prec when float was printed
            fs->precision--;
        }
    return (i);
}

size_t print_ordsymb(const char **s)
{
    size_t  i;

    i = 0;
    while (**s)
    {
        if (**s == '%' /*&& *((*s) + 1) != '\0'*/)
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

void handle_star(t_fs *fs, va_list ap)
{
    if (fs->starw)
        fs->width = va_arg(ap, int);
    if (fs->starp)
        fs->precision = va_arg(ap, int);
}

size_t print(t_fs *fs, va_list ap)
{
    size_t  i;
    ssize_t var;

    i = 0;
    var = va_arg(ap, ssize_t);
    usemodif(fs, var, 0);
    handle_star(fs, ap);
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
        i += padding(fs, ft_wordlen(var));
        i += ft_putnbr(var, 0, fs);
    }
    else if (fs->ch == 'f')
    {
        i += padding(fs, ft_wordlen((ssize_t)var));
        i += ft_putnbr(var, 0, fs);
    }
    fs->width -= i;
    return (i);
}

size_t print_base(t_fs *fs, va_list ap)
{
    size_t  i;
    char    *systemstr;
    char    *str;
    size_t var;

    systemstr = NULL;
    i = 0;
    if (fs->ch != '%')
    {
        var = va_arg(ap, size_t);
        usemodif(fs, 0, var);
        handle_star(fs, ap);
        if (fs->ch == 'X')
            systemstr = "0123456789ABCDEF";
        else if (fs->ch == 'x' || fs->ch == 'p')
            systemstr = "0123456789abcdef";
        else if (fs->ch == 'O' || fs->ch == 'o')
            systemstr = "01234567";
        else if (fs->ch == 'b')
            systemstr = "01";
        str = ft_convert_base(var, systemstr, fs);
    }
    else
        str = ft_strdup("%");
    i += padding(fs, ft_strlen(str));
    i += ft_putstr(str);
    ft_strdel(&str);
    return (i);
}

size_t print_str_fs(t_fs *fs, va_list ap)
{
    size_t  i;

    i = 0;
    //i = padding(fs, 1);
    if (fs->ch)
    {
        if (fs->ch == 'o' || fs->ch == 'O' || fs->ch == 'x' || fs->ch == 'X' || \
            fs->ch == 'u' || fs->ch == 'U' || fs->ch == 'p' || fs->ch == 'b' || \
            fs->ch == '%')
            i += print_base(fs, ap);
        else if (fs->ch == 'd' || fs->ch == 'D' || fs->ch == 's' || fs->ch == 'S' || \
                fs->ch == 'c' || fs->ch == 'C' || fs->ch == 'i' || fs->ch == 'f')
            i += print(fs, ap);
        i += padding_after(fs, i); //??? mb v else if
    }
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
   /* if (r > 9223372036854775807 && sign == -1)
        return (0);
    if (r > 9223372036854775807)
        return (-1);*/
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
    if (ch == 'h')
        fs->h++;
    else if (ch == 'l')
        fs->l++;
    else if (ch == 'L')
        fs->bl++;
    else if (ch == 'z' || ch == 'Z')
        fs->z++;
    else if (ch == 'j')
        fs->j++;
}

void read_conv_mod(t_fs *fs, const char **s)
{
    if (**s == 'o' || **s == 'O' || **s == 'x' || **s == 'X' || \
        **s == 'u' || **s == 'U' || **s == 'p' || **s == 'b' || \
        **s == 'd' || **s == 'D' || **s == 's' || **s == 'S' || \
        **s == 'c' || **s == 'C' || **s == 'i' || **s == 'f' || \
        **s == '%')
        fs->ch = *(*s)++;
}


size_t handle_str_fs(va_list ap, const char **s, t_fs *fs)
{
    while (**s == '-' || **s == '+' || **s == '#' || **s == ' ' || **s == '0')
        handle_flags(fs, *(*s)++);
    if (**s >= '0' && **s <= '9')
        fs->width = ft_atoi_printf(s);
    if (**s == '*')
    {
        fs->starw = 1;
        (*s)++;
    }
    if (**s == '.')
    {
        (*s)++;
        if (**s == '*')
        {
            fs->starp = 1;
            (*s)++;
        }
        else
        {
            fs->precision = ft_atoi_printf(s);
            fs->precision = (fs->precision > 0) ? fs->precision : 0;
        }
    }
    while (**s == 'h' || **s == 'l' || **s == 'L' || **s == 'j' || **s == 'z')
        handle_modif(fs, *(*s)++);
    if (!**s)
        exit(1);
    read_conv_mod(fs, s);
    return (print_str_fs(fs, ap));
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
    fs->starw = 0;
    fs->starp = 0;
    fs->h = 0;
    fs->l = 0;
    fs->j = 0;
    fs->z = 0;
    fs->bl = 0;
}

size_t handstrform(va_list ap, const char *frmt, t_fs *fs)
{
    size_t  i;

    i = 0;
    while (*frmt)
    {
        i += print_ordsymb(&frmt);
        if (*frmt)
        {
            init_flags(fs); //
            i += handle_str_fs(ap, &frmt, fs);
        }
    }
    return (i);
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
        i = handstrform(ap, format, fs);
        ft_memdel((void **)&fs);
    }
    va_end(ap);
    return (i);
}