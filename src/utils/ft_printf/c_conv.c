#include "ft_printf_int.h"

int		c_conv(t_pf *buf, va_list *ap)
{
	push_buf(buf, (char)va_arg(*ap, int));
	return (0);
}
