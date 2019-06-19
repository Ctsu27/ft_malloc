#include <sys/types.h>

// TODO need protection here or in upper function
size_t	round_page_size(size_t size, size_t page_size)
{
	size_t	res;

	res = page_size;
	while (res < size)
	{
		res += page_size;
	}
	return (res);
}
