#include <unistd.h>
#include "ft_printf_int.h"

inline void	put_buf(t_pf *buf)
{
	write(buf->fd, buf->buf, buf->idx);
	buf->idx = 0;
}

inline void	push_buf(t_pf *buf, char c)
{
	if (buf->idx == PF_BUFF_SIZE)
		put_buf(buf);
	buf->buf[buf->idx] = c;
	++(buf->idx);
}
