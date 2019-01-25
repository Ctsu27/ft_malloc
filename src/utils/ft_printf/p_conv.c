#include "ft_printf_int.h"

int		p_conv(t_pf *buf, va_list *ap)
{
	char	str[16];
	size_t	nb;
	int		idx;
	int		n;

	nb = (size_t)va_arg(*ap, size_t);
	push_buf(buf, '0');
	push_buf(buf, 'x');
	if (nb == 0)
		push_buf(buf, '0');
	else
	{
		idx = 0;
		while (nb != 0)
		{
			n = nb % 16;
			str[idx] = g_str_number[n];
			++idx;
			nb /= 16;
		}
		while (--idx >= 0)
			push_buf(buf, str[idx]);
	}
	return (0);
}
