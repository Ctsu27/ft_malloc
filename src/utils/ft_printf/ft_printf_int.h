#ifndef FT_PRINTF_INT_H
# define FT_PRINTF_INT_H

# include <stddef.h>
# include <stdarg.h>
# define PF_BUFF_SIZE			1024
# define PF_STR_NB_HEX_LWCASE	"0123456789abcdef"

typedef struct		s_pf
{
	size_t	idx;
	char	buf[PF_BUFF_SIZE];
	int		fd;
}					t_pf;

extern int			c_conv(t_pf *buf, va_list *ap);
extern int			id_conv(t_pf *buf, va_list *ap);
extern int			p_conv(t_pf *buf, va_list *ap);
extern int			s_conv(t_pf *buf, va_list *ap);
extern int			u_conv(t_pf *buf, va_list *ap);
extern int			x__conv(t_pf *buf, va_list *ap);
extern int			x_conv(t_pf *buf, va_list *ap);
extern void			push_buf(t_pf *buf, char c);
extern void			put_buf(t_pf *buf);
#endif
