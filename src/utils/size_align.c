#include <sys/types.h>

size_t	size_align(size_t size)
{
	if (size < 16)
		return (16);
	return (size + (16 - (size % 16)));
}
