#include <sys/types.h>

#include "utils.h"
size_t	size_align(size_t size)
{
	PRINT_FILE();
	if (size < 16)
		return (16);
	if (size % 16 == 0)
		return (size);
	return (size + (16 - (size % 16)));
}
