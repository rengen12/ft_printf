#include <stdarg.h>
#include "libft/libft.h"

size_t handstr(va_list ap, const char *f)
{
    (void)ap;
    (void)f;
    return (0);
}

int ft_printf (const char *format, ...)
{
    size_t  i;
    va_list ap;

    if (!format)
        return (0);
    va_start(ap, format);
    i = handstr(ap, format);
    va_end(ap);
    return (i);
}