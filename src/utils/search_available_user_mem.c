#include "ft_malloc_int.h"

#include "utils.h"
void	*seach_available_user_mem(const int kind, size_t size)
{
	PRINT_FILE();
	(void)kind;
	t_area	*minju;
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;
	int		idx;

	// if ((minju = g_mdata.izone[kind]) == (t_area *)0)
	// 	return ((void *)0);
	idx = 0;
	while (idx < SIZE_KIND)
	{
		minju = g_mdata.izone[idx];
		while (minju != (t_area *)0)
		{
			chunk = (t_chunk *)(((void *)minju) + sizeof(*minju));
			cur = 0;
			end = (minju->size_map - sizeof(*minju)) / sizeof(*chunk);
			while (cur < end)
			{
				if (chunk->user_mem != (void *)0 && chunk->size_chunk >= size
						&& !chunk->is_used)
				{
					// ft_dpf(2, "=== user mem available [%u]\n", cur);
					chunk->size_user_requested = size;
					chunk->is_used = 1;
					// TODO move chunk to right pool/area
					split_chunk(chunk);
					return (chunk->user_mem);
				}
				chunk = chunk + 1;
				++cur;
			}
			minju = minju->fd;
		}
		++idx;
	}
	// ft_dpf(2, "no user mem available\n");
	return ((void *)0);
}
