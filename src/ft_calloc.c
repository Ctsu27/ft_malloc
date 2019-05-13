#include "ft_malloc_int.h"
#include "malloc.h"
#include "utils.h"

void	*calloc(size_t count, size_t size)
{
	void	*res;
	size_t	total_size;

	total_size = count * size;
	res = malloc(total_size);
	if (res != (void *)0)
		ft_memset(res, 0, total_size);
	return (res);
}
