#include "ft_printf.h"

void read_conv_mod(t_fs *fs, const char **s)
{
	fs->ch = *(*s)++;
	if (fs->ch == 'D' || fs->ch == 'i')
	{
		fs->l = (fs->ch == 'D') ? 1 : fs->l;
		fs->ch = 'd';
	}
	else if (fs->ch == 'U')
	{
		fs->ch = 'u';
		fs->l = 1;
	}
	else if (fs->ch == 'O')
	{
		fs->ch = 'o';
		fs->l = 1;
	}
	else
	{
		fs->ch = (char) ((fs->ch == 'F') ? 'f' : fs->ch);
		fs->sh = (fs->ch == 'p') ? 1 : fs->sh;
	}
}

void init_flags(t_fs *fs)
{
	fs->ch = 0;
	fs->nf = 0;
	fs->sh = 0;
	fs->zero = 0;
	fs->minus = 0;
	fs->plus = 0;
	fs->space = 0;
	fs->width = 0;
	fs->precision = -1;
	fs->apo = 0;
	fs->h = 0;
	fs->l = 0;
	fs->j = 0;
	fs->z = 0;
	fs->prec_exist = 0;
}

size_t handstrform(va_list ap, const char *frmt, t_fs *fs)
{
	size_t i;

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
	size_t i;
	va_list ap;
	t_fs *fs;

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