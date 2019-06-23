#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

#include "ft_printf.h"

void	split_chunk(t_chunk *minju_ga_dooo)
{
	PRINT_FILE();
	t_area	*area;
	t_chunk	*victim;
	size_t	size_chunk;
	int		kind;

	size_chunk = size_align(minju_ga_dooo->size_user_requested);
	// ft_dpf(2, "size chunk -> %u\n", size_chunk);
	if (minju_ga_dooo->size_chunk != size_chunk)
	{
		kind = get_area_kind_by_size(minju_ga_dooo->size_chunk - size_chunk);
		victim = get_meta_chunk_mem((const int)kind);
		if (victim == (t_chunk *)0)
		{
			if ((area = new_meta_mem()) != (t_area *)0
					&& append_area(area, (const int)kind) == 0)
				victim = ((void *)area) + sizeof(*area);
		}
		if (victim != (t_chunk *)0)
		{
			// ft_dpf(2, "%ssplit cpy----------------%s\n", C_B, C_X);
			victim->user_mem = minju_ga_dooo->user_mem + size_chunk;
			victim->size_chunk = minju_ga_dooo->size_chunk - size_chunk;
			victim->is_used = 0;
			minju_ga_dooo->size_chunk = size_chunk;
		}
	}
}

void		*append_to_meta_mem_and_get_user_mem(const int kind,
		void *map, size_t size_map, size_t size_requested)
{
	PRINT_FILE();
	t_area  *minju;
    t_chunk	*minju_ga_dooo;
	size_t	cur;
	size_t	end;
	t_area	*tmp;

	if (map == (void *)0)
		return ((void *)0);
	// ft_dpf(2, "kind === %d\n", kind);
	if (g_mdata.izone[kind] == (t_area *)0
		&& (g_mdata.izone[kind] = new_meta_mem()) == (t_area *)0)
	{
		if (size_map > 0)
			munmap(map, size_map);
		return ((void *)0);
	}
	minju = g_mdata.izone[kind];
	if (minju->fd == (t_area *)0)
	{
		// ft_dpf(2, "first minju\n");
		minju_ga_dooo = (t_chunk *)(((void *)minju) + sizeof(*minju));
		cur = 0;
		end = (minju->size_map - sizeof(*minju)) / sizeof(t_chunk);
		while (cur < end)
		{
			if (minju_ga_dooo->user_mem == (void *)0)
			{
				// ft_dpf(2, "find chunk ! [%u]\n", cur);
				minju_ga_dooo->user_mem = map;
				minju_ga_dooo->size_chunk = size_map;
				minju_ga_dooo->size_user_requested = size_requested;
				minju_ga_dooo->is_used = 1;
				split_chunk(minju_ga_dooo);
				return (minju_ga_dooo->user_mem);
			}
			minju_ga_dooo = minju_ga_dooo + 1;
			++cur;
		}
	}
	else
	{
		// ft_dpf(2, "while minju\n");
		while (minju->fd != (t_area *)0)
		{
			minju_ga_dooo = (t_chunk *)(((void *)minju) + sizeof(*minju));
			cur = 0;
			end = (minju->size_map - sizeof(*minju)) / sizeof(t_chunk);
			while (cur < end)
			{
				if (minju_ga_dooo->user_mem == (void *)0)
				{
					minju_ga_dooo->user_mem = map;
					minju_ga_dooo->size_chunk = size_map;
					minju_ga_dooo->size_user_requested = size_requested;
					minju_ga_dooo->is_used = 1;
					split_chunk(minju_ga_dooo);
					return (minju_ga_dooo->user_mem);
				}
				minju_ga_dooo = minju_ga_dooo + 1;
				++cur;
			}
			// ft_dpf(2, "==================> %u -> %u\n", cur, end);
			minju = minju->fd;
		}
		if (cur == end)
		{
			tmp = new_meta_mem();
			if (tmp != (t_area *)0)
			{
				append_area(tmp, kind);
				minju = g_mdata.izone[kind];
				while (minju->fd != (t_area *)0)
				{
					minju_ga_dooo = (t_chunk *)(((void *)minju) + sizeof(*minju));
					cur = 0;
					end = (minju->size_map - sizeof(*minju)) / sizeof(t_chunk);
					while (cur < end)
					{
						if (minju_ga_dooo->user_mem == (void *)0)
						{
							minju_ga_dooo->user_mem = map;
							minju_ga_dooo->size_chunk = size_map;
							minju_ga_dooo->size_user_requested = size_requested;
							minju_ga_dooo->is_used = 1;
							split_chunk(minju_ga_dooo);
							return (minju_ga_dooo->user_mem);
						}
						minju_ga_dooo = minju_ga_dooo + 1;
						++cur;
					}
					// ft_dpf(2, "==================> %u -> %u\n", cur, end);
					minju = minju->fd;
				}
			}
		}
	}
	return ((void *)0);
}
