#include "ft_malloc_int.h"

#include "utils.h"
int		get_area_kind_by_size(const size_t size)
{
	PRINT_FILE();
	static const size_t max = ((((size_t)(-1)) / 2));

	if (size > max)
		return (NONE);
	if (size <= TINY_SIZE)
		return (TINY);
	if (size <= SMALL_SIZE)
		return (SMALL);
	return (LARGE);
}
