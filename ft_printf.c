#include "ft_printf.h"

void usemodifu(t_fs *fs, size_t *valu)
{
    if (fs->h && *valu && !fs->l)
        if (fs->h == 1)
            *valu = (unsigned short int)*valu;
        else
            *valu = (unsigned char)*valu;
    else if (fs->l && *valu)
        if (fs->l == 1)
            *valu = (unsigned long int)*valu;
        else
            *valu = (unsigned long long int)*valu;
    else if (fs->j && *valu)
        *valu = (uintmax_t)*valu;
    else if (fs->z)
        *valu = (size_t)*valu;
    else
        *valu = (unsigned int)*valu;
}

void usemodifs(t_fs *fs, ssize_t *vals)
{
    if (fs->h && *vals && !fs->l)
        if (fs->h == 1)
            *vals = (short int)*vals;
        else
            *vals = (char)*vals;
    else if (fs->l && *vals)
        if (fs->l == 1)
            *vals = (long int)*vals;
        else
            *vals = (long long int)*vals;
    else if (fs->bl)
        *vals = (long double)*vals;
    else if (fs->j && *vals)
        *vals = (intmax_t)*vals;
    else if (fs->z)
        *vals = (size_t)*vals;
    else
        *vals = (int)*vals;
}

size_t padding(t_fs *fs, int wordlen)
{
    size_t i;

    i = 0;
    if ((fs->zero && fs->precision != 1) || (fs->zero && fs->minus))
        fs->zero = 0;
    else if (fs->zero)
        fs->precision = fs->width;
    while (fs->width > /*fs->precision - */wordlen && !fs->minus && !fs->zero && fs->precision < fs->width)
    {
        i += ft_putchar(' ');
        fs->width--;
    }
    if (fs->ch != 'f' && fs->ch != 'd' && fs->ch != 'i')
        while (fs->precision > wordlen && fs->ch != 'c' && fs->ch != 'C')
        {
            i += ft_putchar('0');
            fs->precision--;
        }
    return (i);
}

size_t padding_str(t_fs *fs, int wordlen)
{
    size_t i;

    i = 0;
    if ((fs->zero && fs->precision != 1) || (fs->zero && fs->minus))
        fs->zero = 0;
    else if (fs->zero)
        fs->precision = fs->width;
    while (fs->width > wordlen && !fs->minus && !fs->zero)
    {
        i += ft_putchar(' ');
        fs->width--;
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


int     ft_wordlen(ssize_t var, t_fs *fs)
{
    int     i;

    i = 0;
    if (var < 0 || fs->plus)
        i++;
    while (var)
    {
        var /= 10;
        i++;
    }
    if (!i)
        i = 1;
    return (i);
}

void handle_star(t_fs *fs, va_list ap)
{
    if (fs->starw)
        fs->width = va_arg(ap, int);
    if (fs->starp)
        fs->precision = va_arg(ap, int);
}

size_t padding_afsign(t_fs *fs, int wordlen)
{
    size_t i;

    i = 0;
    while (fs->precision > wordlen)
    {
        i += ft_putchar('0');
        fs->precision--;
    }
    return (i);
}

size_t print_num(t_fs *fs, va_list ap)
{
    ssize_t var;
    size_t  i;

    i = 0;
    var = va_arg(ap, ssize_t);
    handle_star(fs, ap);
    usemodifs(fs, &var);
    if (!fs->precision && !var)
        i += padding(fs, 0);
    else
    {
        i += padding(fs, ft_wordlen(var, fs));
        i += ft_putnbr(var, fs);
    }
    fs->width -= i;
    return (i);
}
size_t handle_sharp(size_t nb, t_fs *fs)
{
    size_t  i;

    i = 0;
    if (fs->zero)
    {
        if (nb && fs->ch == 'x' && fs->sh)
            i += ft_putstr("0x", fs);
        else if (nb && fs->ch == 'X' && fs->sh)
            i += ft_putstr("0X", fs);
        else if (nb && (fs->ch == 'o' || fs->ch == 'O') && fs->sh)
            i += ft_putstr("0", fs);
    }
    //fs->width -= i;
    return (i);
}
size_t print_unsig(t_fs *fs, va_list ap)
{
    size_t  i;
    char    *systemstr;
    char    *str;
    size_t var;

    systemstr = NULL;
    i = 0;
    handle_star(fs, ap);
    var = va_arg(ap, size_t);
    usemodifu(fs, &var);
    i += handle_sharp(var, fs);
    if (fs->ch == 'u')
        systemstr = "0123456789";
    if (fs->ch == 'X')
        systemstr = "0123456789ABCDEF";
    else if (fs->ch == 'x' || fs->ch == 'p')
        systemstr = "0123456789abcdef";
    else if (fs->ch == 'O' || fs->ch == 'o')
        systemstr = "01234567";
    else if (fs->ch == 'b')
        systemstr = "01";
    str = ft_convert_base(var, systemstr, fs);
    i += padding(fs, ft_strlen(str) + i);
    i += ft_putstr(str, fs);
    ft_strdel(&str);
    return (i);
}

size_t print_float(t_fs *fs, va_list ap)
{
    size_t  i;
    double  var;
    //ssize_t vardoub;

    i = 0;
    var = va_arg(ap, double);
    i += ft_putnbr((int)var, fs);
    i += ft_putchar('.');
    //i += ft_putnbr(, fs);
    return (i);
}

size_t print_string(t_fs *fs, va_list ap)
{
    size_t  i;
    char *str;
    size_t  l;

    i = 0;
    str = va_arg(ap, char *);
    l = ft_strlen(str);
    l = (l > (size_t)fs->precision && fs->precision != 1) ? (size_t)fs->precision : l;
    i += padding_str(fs, l);
    if (!str)
        i += ft_putstr("(null)", fs);
    else if (fs->ch == 's')
        i += ft_putstr(str, fs);
    else if (fs->ch == 'S')
        i += ft_putstr_u(str, fs);
    return (i);
}

size_t print_char(t_fs *fs, va_list ap)
{
    size_t  i;
    int     var;

    i = 0;
    var = va_arg(ap, int);
    i += padding(fs, 1);
    if (fs->ch == 'c')
        i += ft_putchar((char)var);
    else if (fs->ch == 'C')
        i += ft_putchar_u(var);
    else if (fs->ch == '%')
        i += ft_putchar('%');
    return (i);
}

size_t print_str_fs(t_fs *fs, va_list ap)
{
    size_t  i;

    i = 0;
    if (fs->ch)
    {
        if (fs->ch == 'o' || fs->ch == 'O' || fs->ch == 'x' || fs->ch == 'X' || \
            fs->ch == 'u' || fs->ch == 'U' || fs->ch == 'b')
            i += print_unsig(fs, ap);
        else if (fs->ch == 'd' || fs->ch == 'i' )
            i += print_num(fs, ap);
        else if (fs->ch == 'f')
            i += print_float(fs, ap);
        else if (fs->ch == 's' || fs->ch == 'S')
            i += print_string(fs, ap);
        else if (fs->ch == 'c' || fs->ch == 'C' || fs->ch == '%')
            i += print_char(fs, ap);
        i += padding_after(fs, i);
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
        **s == 'u' || **s == 'b' || \
        **s == 'd' || **s == 's' || **s == 'S' || **s == 'c' ||
        **s == 'C' || **s == 'i' || **s == 'f' || **s == '%')
        fs->ch = *(*s)++;
    else if (**s == 'D')
    {
        (*s)++;
        fs->ch = 'd';
        fs->l = 1;
    }
    else if (**s == 'p')
    {
        (*s)++;
        fs->ch = 'x';
        fs->sh = 1;
    }
    else if (**s == 'U')
    {
        (*s)++;
        fs->ch = 'u';
        fs->l = 1;
    }
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
            init_flags(fs);
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