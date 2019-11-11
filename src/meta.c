#include <unistd.h>
#include "ft_malloc_int.h"

t_meta	g_mdata;

__CONSTRUCTOR	init_meta(void)
{
	g_mdata.page_size = getpagesize();
	g_mdata.nako = (t_area *)0;
	g_mdata.yena = (t_area *)0;
	g_mdata.wonyoung = (t_area *)0;
}
