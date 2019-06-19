#include "ft_malloc_int.h"
#include "utils.h"

#include "ft_printf.h"

void	split_chunk(t_chunk *minju_ga_dooo)
{
	t_area	*area;
	t_chunk	*victim;
	t_chunk	chunk;
	size_t	size_chunk;
	int		kind;

	size_chunk = size_align(minju_ga_dooo->size_user_requested);
	if (minju_ga_dooo->size_chunk != size_chunk)
	{
		chunk.user_mem = minju_ga_dooo->user_mem + size_chunk;
		chunk.size_chunk = minju_ga_dooo->size_chunk - size_chunk;
		chunk.is_freed = 1;
		kind = get_area_kind_by_size((const size_t)chunk.size_chunk);
		if (kind == NONE)
		{
			ft_dpf(2, "kind == NONE, should not be possible in %s:%u\n", __func__, __LINE__);
		}
		victim = get_meta_chunk_mem((const int)kind);
		if (victim == (t_chunk *)0)
		{
			if ((area = new_meta_mem()) != (t_area *)0
					&& append_area(area, (const int)kind) == 0) // TODO
				victim = ((void *)area) + sizeof(*area);
		}
		if (victim != (t_chunk *)0)
		{
			minju_ga_dooo->size_chunk = size_chunk;
			*victim = chunk; // TODO change this to prevent memcpy call
		}
	}
}

void	*append_to_meta_mem_and_get_user_mem(const int kind,
		void *map, size_t size_map, size_t size_requested)
{
	t_area  **minju;
    t_chunk	*minju_ga_dooo;
	size_t	cur;
	size_t	end;

	if (map == (void *)0)
		return ((void *)0);
	if (g_mdata.izone[kind] == (t_area *)0)
		g_mdata.izone[kind] = new_meta_mem();
	minju = &g_mdata.izone[kind];
	while ((*minju)->fd != (t_area *)0)
	{
		minju_ga_dooo = (t_chunk *)(((void *)(*minju)) + sizeof(**minju));
		cur = 0;
		end = ((*minju)->size_map - sizeof(**minju)) / sizeof(t_chunk);
		while (cur < end)
		{
			if (minju_ga_dooo->user_mem == (void *)0)
			{
				minju_ga_dooo->user_mem = map;
				minju_ga_dooo->size_chunk = size_map;
				minju_ga_dooo->size_user_requested = size_requested;
				minju_ga_dooo->is_freed = 0;
				split_chunk(minju_ga_dooo);
				return (minju_ga_dooo->user_mem);
			}
			minju_ga_dooo = minju_ga_dooo + 1;
			++cur;
		}
		minju = &((*minju)->fd);
	}
	return ((void *)0);
}
