#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

#include "malloc.h"
void			free(void *ptr)
{
	PRINT_FILE();

	if (ptr == (void *)0)
		return ;
}

__DESTRUCTOR	garbage_collector(void)
{
	PRINT_FILE();
}
