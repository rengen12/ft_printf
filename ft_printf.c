#include "ft_printf.h"

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
    return (i);
}

size_t print_str_fs(t_fs *fs, void *var)
{

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
void handle_modif(t_fs *fs, const char **s)
{
    if (**s++ == 'h')//test it
    {
        if (**s == 'h') //endofwork
        {
            fs->hh = 1;
            return;
        }
    }

}

size_t handle_str_fs(va_list ap, const char **frmt, t_fs *fs)
{
    size_t  i;
    char    *s;

    i = 0;
    s = *(char **)frmt;
    while (*s == '-' || *s == '+' || *s == '#' || *s == ' ' || *s == '0')
        handle_flags(fs, *s++);
    if (ft_isdigit(*s))
        fs->width = ft_atoi_printf(&s);
    if (*s == '.')
        fs->precision = ft_atoi_printf(&++s);
    if (*s == 'h' || *s == 'l' || *s == 'L')
        handle_modif(fs, &s);
    if (*s)
        exit(1);
    fs->ch = *s++;
    //i = print_str_fs(fs, var); //передать переменную со значением для выведения
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
    fs->hh = 0;
    fs->h = 0;
    fs->l = 0;
    fs->ll = 0;
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