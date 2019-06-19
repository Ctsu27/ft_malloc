#include "ft_malloc_int.h"

int		get_area_kind_by_size(const size_t size)
{
	static const size_t max = ((((size_t)(-1)) / 2));

	if (size <= 0 || size > max)
		return (NONE);
	if (size <= TINY_SIZE)
		return (TINY);
	if (size <= SMALL_SIZE)
		return (SMALL);
	return (LARGE);
}
