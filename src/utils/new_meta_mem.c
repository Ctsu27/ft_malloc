#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

t_area	*new_meta_mem(void)
{
	PRINT_FILE();
	t_area	*res;

	if ((res = mmap((void *)0, (size_t)g_mdata.page_size,
				PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0)) != MAP_FAILED)
	{
		// ft_dpf(2, "%sMAP META: %s%p%s\n", C_G, C_Y, res, C_X);
		ft_memset((void *)res, 0, (size_t)g_mdata.page_size);
		res->bk = (t_area *)0;
		res->fd = (t_area *)0;
		res->size_map = (size_t)g_mdata.page_size;
		res->fill = 0;
	}
	else
		return ((void *)0);
	return (res);
}
