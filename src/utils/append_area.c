#include "ft_malloc_int.h"

int		append_area(t_area *area, const int kind)
{
	t_area	*minju;

	minju = g_mdata.izone[kind];
	while (minju->fd != (t_area *)0)
		minju = minju->fd;
	minju->fd = area;
	area->bk = minju;
	return (0);
}
