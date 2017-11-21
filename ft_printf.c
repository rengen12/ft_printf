#include <stdarg.h>
#include "libft/libft.h"

int ft_printf (const char *format, ...)
{
    int     i;
    va_list ap;
    char *n;
    int n2;

    va_start(ap, i);
    if (!format)
        return (0);
    ft_putendl("i");
    ft_putnbr(i);
    ft_putendl("");
    ft_putendl("");
    n = va_arg(ap, char *);
    ft_putendl("");
    ft_putchar(n);
    n = va_arg(ap, int);
    ft_putnbr(n);
    /*while(format[i])
    {
        if (format[i] == '%')
        {
            if (format[i + 1] == '%')
                ft_putchar('%');
            ft_putchar(va_arg());
        }
        ft_putchar(format[i++]);
    }*/
    return (i);
}