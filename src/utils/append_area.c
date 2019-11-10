#include "ft_malloc_int.h"

#include "utils.h"
int		append_area(t_area *area, const int kind)
{
	PRINT_FILE();
	t_area	*minju;

	if (area == (t_area *)0)
		return (-1);
	minju = g_mdata.izone[kind];
	if (minju == (t_area *)0)
		g_mdata.izone[kind] = area;
	else
	{
		while (minju->fd != (t_area *)0)
			minju = minju->fd;
		minju->fd = area;
		area->bk = minju;
	}
	return (0);
}
