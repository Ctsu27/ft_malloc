#include "ft_printf_int.h"

char const			*g_str_number = "0123456789abcdef";

static const _Bool	g_is_convert[256] = \
{
	['X'] = 1,
	['c'] = 1,
	['d'] = 1,
	['i'] = 1,
	['p'] = 1,
	['s'] = 1,
	['u'] = 1,
	['x'] = 1
};
static int			(*g_converter[256])(t_pf *, va_list *) = \
{
	['X'] = &x__conv,
	['c'] = &c_conv,
	['d'] = &id_conv,
	['i'] = &id_conv,
	['p'] = &p_conv,
	['s'] = &s_conv,
	['u'] = &u_conv,
	['x'] = &x_conv
};

static void	print_format(t_pf *buf, const char *fmt, va_list *ap)
{
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			++fmt;
			if (g_is_convert[(int)*fmt])
				g_converter[(int)*fmt](buf, ap);
		}
		else
			push_buf(buf, *fmt);
		++fmt;
	}
	put_buf(buf);
}

int			ft_dpf(int fd, const char *fmt, ...)
{
	t_pf	buf;
	va_list	ap;

	if (fmt == NULL)
		return (-1);
	buf.idx = 0;
	buf.fd = fd;
	va_start(ap, fmt);
	print_format(&buf, fmt, &ap);
	va_end(ap);
	return (buf.idx);
}

int			ft_pf(const char *fmt, ...)
{
	t_pf	buf;
	va_list	ap;

	if (fmt == NULL)
		return (-1);
	buf.idx = 0;
	buf.fd = 1;
	va_start(ap, fmt);
	print_format(&buf, fmt, &ap);
	va_end(ap);
	return (buf.idx);
}
