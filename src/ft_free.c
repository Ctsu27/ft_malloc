#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

#include "malloc.h"
void			free(void *ptr)
{
	PRINT_FILE();
	t_chunk	*meta;

	if (ptr == (void *)0)
		return ;
	meta = find_chunk_by_user_mem(ptr);
	if (meta != NULL)
	{
		// make unused;
	}
}
