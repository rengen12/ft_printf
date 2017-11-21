#include <stdarg.h>
#include "libft/libft.h"

size_t handstr(va_listap, size_t i){

    return ();
}

int ft_printf (const char *format, ...)
{
    size_t  i;
    va_list ap;

    if (!format)
        return (0);
    va_start(ap, i);
    i = handstr(ap, i);
    va_end(ap);
    return (i);
}