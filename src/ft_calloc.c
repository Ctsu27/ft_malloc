#include "malloc.h"
#include "utils.h"

#include "ft_printf.h"
void	*calloc(size_t count, size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	void	*res;
	size_t	total_size;

	total_size = count * size;
	res = malloc(total_size);
	if (res != (void *)0)
		ft_memset(res, 0, total_size);
	return (res);
}
