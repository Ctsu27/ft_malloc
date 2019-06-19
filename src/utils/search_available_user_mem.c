#include "ft_malloc_int.h"

void	*seach_available_user_mem(const int kind, size_t size)
{
	t_area	*minju;
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;

	if ((minju = g_mdata.izone[kind]) == (t_area *)0)
		return ((void *)0);
	while (minju != (t_area *)0)
	{
		chunk = (t_chunk *)(((void *)minju) + sizeof(*minju));
		cur = 0;
		end = (minju->size_map - sizeof(*minju)) / sizeof(*chunk);
		while (cur < end)
		{
			if (chunk->user_mem != (void *)0 && chunk->size_chunk >= size)
			{
				chunk->size_user_requested = size;
				chunk->is_freed = 0;
				return (chunk->user_mem);
			}
			chunk = chunk + 1;
			++cur;
		}
		minju = minju->fd;
	}
	return ((void *)0);
}
