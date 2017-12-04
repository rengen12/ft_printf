#include "ft_printf.h"

size_t padding(char cs, size_t width, size_t prec, size_t wordlen)
{
    size_t i;

    i = 0;
    while (width-- > prec - wordlen)
        i += ft_putchar(' ');
    if (cs != 'f')
        while (prec-- > wordlen)
            i += ft_putchar('0');
    return (i);
}

size_t print_ordsymb(const char **frmt)
{
    char    *s;
    size_t  i;

    s = *(char **)frmt;
    i = 0;
    while (*s != 0)
    {
        if (*s == '%')
           if (*++s != '%')
               break ;
        ft_putchar_u(*s++);
        i++;
    }
    *frmt = s;
    return (i);
}


size_t print(t_fs *fs, ssize_t var)
{
    size_t  i;

    i = 0;
    if (fs->ch == 'c')
        ft_putchar((char)var);
    else if (fs->ch == 's')
        ft_putstr((char *)var);
    else if (fs->ch == 'C')
        i = ft_putchar_u((int)var);
    else if (fs->ch == 'S')
        i = ft_putstr_u((char *)var);

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
    padding(fs->ch, fs->width, fs->precision, (i = ft_strlen(str)));
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
            fs->ch == 'c' || fs->ch == 'C')
        i += print(fs, va_arg(ap, ssize_t));
    return (i);
}

void handle_flags(t_fs *fs, char curch)
{

    if (curch == '-')
        fs->minus = 1;
    else if (curch == '+')
        fs->plus = 1;
    else if (curch == '#')
        fs->sh = 1;
    else if (curch == ' ')
        fs->space = 1;
    else if (curch == '0')
        fs->zero = 1;
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

void handle_modif(t_fs *fs, char s)
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
    if (s == 'h')
        fs->h++;
    else if (s == 'l')
        fs->l++;
    else if (s == 'L')
        fs->bl++;
    else if (s == 'z')
        fs->z++;
    else if (s == 'j')
        fs->j++;
}

size_t handle_str_fs(va_list ap, const char **frmt, t_fs *fs)
{
    size_t        i;
    const char    *s;

    i = 0;
    s = *frmt;
    while (*s == '-' || *s == '+' || *s == '#' || *s == ' ' || *s == '0')
        handle_flags(fs, *s++);
    if (ft_isdigit(*s))
        fs->width = ft_atoi_printf(&s);
    if (*s == '.')
        fs->precision = ft_atoi_printf(&s);
    while (*s == 'h' || *s == 'l' || *s == 'L' || *s == 'j' || *s == 'z')
        handle_modif(fs, *s++);
    if (!*s)
        exit(1);
    fs->ch = *s++;
    i += print_str_fs(fs, ap);
    *frmt = s;
    return (i);
}

size_t handstrform(va_list ap, const char *frmt, t_fs *fs)
{
    size_t  i;

    i = 0;
    while (*frmt)
    {
        i += print_ordsymb(&frmt);
        if (*frmt != 0)
            i += handle_str_fs(ap, &frmt, fs); //передваемый параметр ва_лист. Можно передавать переменную со значением, а не весь лист
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
    fs->precision = 0;
    fs->h = 0;
    fs->l = 0;
    fs->j = 0;
    fs->z = 0;
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