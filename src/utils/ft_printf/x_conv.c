#include "ft_printf_int.h"

int		x_conv(t_pf *buf, va_list *ap)
{
	char			str[10];
	unsigned int	nb;
	int				idx;
	int				n;

	nb = (unsigned int)va_arg(*ap, unsigned int);
	if (nb == 0)
		push_buf(buf, '0');
	else
	{
		idx = 0;
		while (nb != 0)
		{
			n = nb % 16;
			str[idx++] = PF_STR_NB_HEX_LWCASE[n];
			nb /= 16;
		}
		while (--idx >= 0)
			push_buf(buf, str[idx]);
	}
	return (0);
}
