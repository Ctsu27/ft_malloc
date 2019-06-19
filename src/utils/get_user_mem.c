#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

void	*get_user_mem(const int kind, size_t size)
{
	size_t	size_map;
    void	*mem_for_user;

	mem_for_user = seach_available_user_mem(kind, size);
	if (mem_for_user == (void *)0)
	{
		size_map = round_page_size(size, g_mdata.page_size);
		mem_for_user = append_to_meta_mem_and_get_user_mem(kind,
				new_user_mem(size_map), size_map, size);
	}
	return (mem_for_user);
}
