#include "ft_printf_int.h"

int		s_conv(t_pf *buf, va_list *ap)
{
	char	*str;

	str = (char *)va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	while (*str != '\0')
	{
		push_buf(buf, *str);
		++str;
	}
	return (0);
}
