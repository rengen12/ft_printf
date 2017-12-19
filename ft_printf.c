#include "ft_printf.h"

size_t padding(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	if (((fs->zero && fs->prec_exist) && ft_strchr("oxXubdsSifpf", fs->ch)) || (fs->zero && fs->minus))
		fs->zero = 0;
	else if (fs->zero)
		fs->precision = ((fs->plus) || (fs->nf && !fs->plus) || fs->space) ? fs->width - 1 : fs->width;
	while (fs->width > wordlen + (fs->nf || fs->plus) + fs->space && !fs->minus && !fs->zero &&
		   fs->precision + (fs->nf || fs->plus) + fs->space < fs->width)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	if ((fs->ch != 'f' && fs->ch != 'd' && fs->ch != '%') || (fs->ch == '%' && fs->zero))
		while (fs->precision > wordlen && (((fs->ch == 'c' || fs->ch == 'C') && \
				fs->zero) || (fs->ch != 'c' && fs->ch != 'C')))
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
	while (fs->width > wordlen && fs->minus && fs->ch != 'f')
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	if (fs->ch == 'f')
		while (fs->precision > 0)
		{
			i += ft_putchar('0');
			fs->precision--;
		}
	return (i);
}

size_t print_ordsymb(const char **s)
{
	size_t		i;

	i = 0;
	while (**s)
	{
		if (**s == '{')
		{
			parse_color(s);
		}
		if (**s == '%')
		{
			if (*(*s)++ == '%')
				;
			break;
		}
		i += ft_putchar(*(*s)++);
	}
	return (i);
}


int ft_wordlen(ssize_t var)
{
	int i;

	i = 0;
	while (var)
	{
		var /= 10;
		i++;
	}
	if (!i)
		i = 1;
	return (i);
}

size_t padding_afsign(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	while (fs->precision > wordlen && fs->ch != 'f')
	{
		i += ft_putchar('0');
		fs->precision--;
	}
	return (i);
}

size_t print_num(t_fs *fs, va_list ap)
{
	ssize_t var;
	size_t i;

	i = 0;
	//handle_star(fs, ap);
	var = va_arg(ap, ssize_t);
	//var = va_arg(ap, ssize_t);//lel
	usemodifs(fs, &var);
	if (var < 0)
		fs->nf = 1;
	if (!fs->precision && !var)
		i += padding(fs, 0);
	else
	{
		i += padding(fs, ft_wordlen(var));
		i += ft_putnbr(var, fs);
	}
	return (i);
}

size_t handle_sharp(size_t nb, t_fs *fs)
{
	size_t i;

	i = 0;
	if (fs->zero)
	{
		if ((nb && fs->ch == 'x' && fs->sh) || fs->ch == 'p')
			i += ft_putstr("0x", fs);
		else if (nb && fs->ch == 'X' && fs->sh)
			i += ft_putstr("0X", fs);
		else if (nb && (fs->ch == 'o' || fs->ch == 'O') && fs->sh)
			i += ft_putstr("0", fs);
	}
	return (i);
}

size_t print_unsig(t_fs *fs, va_list ap)
{
	size_t i;
	char *systemstr;
	char *str;
	size_t var;

	i = 0;
	var = va_arg(ap, size_t);
	usemodifu(fs, &var);
	i += handle_sharp(var, fs);
	if (fs->ch == 'u' && (systemstr = NULL) == NULL)
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
	size_t i;
	long double var;

	i = 0;
	if (fs->l)
		var = va_arg(ap, long double);//dont work with big num
	else
		var = va_arg(ap, double);
	if (var < 0)
	{
		var *= -1;
		fs->nf = 1;
	}
	i += ft_putnbr((size_t)var, fs);//rework for big num
	fs->nf = 0;
	if (fs->precision == -1)
		fs->precision = 6;
	if (fs->precision > 0)
		i += ft_putchar('.');
	while (fs->precision-- > 0)
	{
		var -= (size_t)var;
		var += 0.000000000001;
		var *= 10;
		i += ft_putnbr((size_t)var, fs);
	}
	return (i);
}

size_t padding_str(t_fs *fs, int wordlen)
{
	size_t i;

	i = 0;
	if (((fs->zero && fs->minus)) && fs->ch != 'S')
		fs->zero = 0;
	else if (fs->zero)
		fs->precision = fs->width;
	while (fs->width > wordlen && !fs->minus && !fs->zero)
	{
		i += ft_putchar(' ');
		fs->width--;
	}
	while (fs->precision > wordlen && fs->zero)
	{
		i += ft_putchar('0');
		fs->precision--;
	}
	return (i);
}

size_t print_string(t_fs *fs, va_list ap)
{
	size_t i;
	char *str;
	size_t l;

	i = 0;
	str = va_arg(ap, char *);
	if (fs->ch == 'S' || (fs->ch == 's' && fs->l))
		l = ft_strlen_u(str, fs);
	else
		l = ft_strlen(str);
	if (!str)
		l = 6;
	l = (l > (size_t)fs->precision && fs->prec_exist) ? (size_t)fs->precision : l;
	i += padding_str(fs, l);
	if (!str)
		i += ft_putstr("(null)", fs);
	else if (fs->ch == 's' && fs->l == 0)
		i += ft_putstr(str, fs);
	else if (fs->ch == 'S' || (fs->ch == 's' && fs->l))
		i += ft_putnstr_u(str, l);
	return (i);
}

size_t print_char(t_fs *fs, va_list ap)
{
	size_t	i;
	int		var;

	i = 0;
	i += padding(fs, 1);
	if (fs->ch == '%')
		i += ft_putchar('%');
	else
		var = va_arg(ap, int);
	if(fs->ch != '%')
	{
		if (fs->ch == 'c' && fs->l == 0)
			i += ft_putchar((char) var);
		else if (fs->ch == 'C' || (fs->ch == 'c' && fs->l))
			i += ft_putchar_u(var);
	}
	return (i);
}

size_t print_str_fs(t_fs *fs, va_list ap)
{
	size_t i;

	if ((i = 0) == 0 && ft_strchr("oxXubdsScCif%pf", fs->ch))
	{
		if (fs->ch == 'f')
			i += print_float(fs, ap);
		else if (fs->ch == 's' || fs->ch == 'S')
			i += print_string(fs, ap);
		else if (fs->precision == -1)
			fs->precision = 1;
		if (ft_strchr("oxXubp", fs->ch))
			i += print_unsig(fs, ap);
		else if (fs->ch == 'd')
			i += print_num(fs, ap);
		else if (fs->ch == 'c' || fs->ch == 'C' || fs->ch == '%')
			i += print_char(fs, ap);
		i += padding_after(fs, i);
	}
	else
	{
		i += padding(fs, 1);
		i += ft_putchar(fs->ch);
		i += padding_after(fs, i);
	}
	return (i);
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
	else if (ch == 'l' || ch == 'L')
		fs->l++;
	else if (ch == 'z' || ch == 'Z')
		fs->z++;
	else if (ch == 'j')
		fs->j++;
}

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

void	handle_str_point(va_list ap, const char **s, t_fs *fs)
{
	(*s)++;
	if (**s == '*')
	{
		fs->precision = va_arg(ap, int);
		fs->precision = (fs->precision < 0 && fs->zero) ? fs->width : fs->precision;
		(*s)++;
	}
	else
	{
		fs->precision = ft_atoi_printf(s);
		fs->precision = (fs->precision > 0) ? fs->precision : 0;
	}
	fs->prec_exist = 1;
}

size_t handle_str_fs(va_list ap, const char **s, t_fs *fs)
{
	while (**s == '-' || **s == '+' || **s == '#' || **s == ' ' || **s == '0')
		handle_flags(fs, *(*s)++);
	while ((**s >= '0' && **s <= '9') || **s == '*')
		if (**s == '*')
		{
			fs->width = va_arg(ap, int);
			if (fs->width < 0)
				fs->minus = 1;
			fs->width = ABS(fs->width);
			(*s)++;
		}
		else
			fs->width = ft_atoi_printf(s);
	while (**s == '.')
		handle_str_point(ap, s, fs);
	while (**s == 'h' || **s == 'l' || **s == 'L' || **s == 'j' || **s == 'z')
		handle_modif(fs, *(*s)++);
	while (**s == '-' || **s == '+' || **s == '#' || **s == ' ' || **s == '0')
		handle_flags(fs, *(*s)++);
	if (!**s)
		return (0);
	read_conv_mod(fs, s);
	return (print_str_fs(fs, ap));
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