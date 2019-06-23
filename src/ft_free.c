/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:51 by kehuang           #+#    #+#             */
/*   Updated: 2019/02/18 00:50:52 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

#include "malloc.h"
void	free(void *ptr)
{
	PRINT_FILE();
	// ft_dpf(2, "%sFree X: %s%p%s\n", C_P, C_Y, ptr, C_X);
	t_chunk	*chunk;

	if (ptr == (void *)0)
		return ;
	chunk = find_chunk_by_ptr(ptr);
	if (chunk != (t_chunk *)0)
	{
		// ft_dpf(2, "%sFreeing address: %s%p%s\n", C_P, C_Y, ptr, C_X);
		chunk->size_user_requested = 0;
		chunk->is_used = 0;
		// ft_dpf(2, "ca crash ???\n");
	}
}

void	delete_chunks_from_pool(t_area *pool)
{
	t_chunk	*chunk;
	size_t	cur;
	size_t	end;

	chunk = (t_chunk *)(((void *)pool) + sizeof(*pool));
	cur = 0;
	end = (pool->size_map - sizeof(*pool)) / sizeof(*chunk);
	while (cur < end)
	{
		if (chunk->user_mem != (void *)0 && chunk->size_chunk > 0)
		{
			ft_dpf(2, "%s_________ END%s ---> %smunmap%s() : %s[%p] [%u]%s\n",
				   C_G, C_X,
				   C_R, C_X,
				   C_Y, (void *)chunk, chunk->size_chunk, C_X);
			munmap((void *)chunk, chunk->size_chunk);
		}
		chunk = chunk + 1;
		++cur;
	}
}

__attribute__((destructor))
void	garbage_collector(void)
{
	PRINT_FILE();
	show_alloc_mem();
	t_area	*pool;
	t_area	*victim;
	int		idx;

	idx = 0;
	while (idx < SIZE_KIND)
	{
		pool = g_mdata.izone[idx];
		while (pool != (t_area *)0)
		{
			victim = pool;
			pool = pool->fd;
			delete_chunks_from_pool(victim);
			// ft_dpf(2, "%s_________ END%s ---> %smunmap%s() : %s[%p] [%u]%s\n",
			// 	C_G, C_X,
			// 	C_R, C_X,
			// 	C_Y, (void *)victim, victim->size_map, C_X);
			munmap((void *)victim, victim->size_map);
		}
		++idx;
	}
}
