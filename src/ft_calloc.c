#include "malloc.h"
#include "utils.h"

#include "ft_printf.h"
void	*calloc(size_t count, size_t size)
{
	PRINT_FILE();
	void	*res;
	size_t	total_size;

	total_size = count * size;
	res = malloc(total_size);
	if (res != (void *)0)
		ft_memset(res, 0, total_size);
	return (res);
}
