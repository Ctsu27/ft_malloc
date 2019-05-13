/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:52 by kehuang           #+#    #+#             */
/*   Updated: 2019/02/18 21:56:25 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include "ft_malloc_int.h"
#include "utils.h"


#include "ft_printf.h"
t_meta	g_data = {
	.nako = (t_area){
		.map = (t_mem *)0,
		.size = 0
	},
	.yena = (t_area){
		.map = (t_mem *)0,
		.size = 0
	},
	.wonyoung = (t_area){
		.map = (t_mem *)0,
		.size = 0
	},
	.page_size = 0
};

int		get_area_kind_by_size(const size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	static const size_t max = ((((size_t)(-1)) / 2));

	if (size <= TINY_SIZE)
		return (TINY);
	if (size <= SMALL_SIZE)
		return (SMALL);
	if (size <= 0 || size > max)
		return (NONE);
	return (LARGE);
}

size_t	get_nako_size_map(__attribute__((__unused__))const size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	return (g_data.nako.size);
}

size_t	get_yena_size_map(__attribute__((__unused__))const size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	if (DEBUG_DPF)
		ft_dpf(2, "yena page size -> %u\n", g_data.yena.size);
	return (g_data.yena.size);
}

size_t	get_wonyoung_size_map(register const size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	register size_t	val;

	val = 0;
	while (val < size)
		val += g_data.page_size;
	return (val);
	// size_t	mod;
	// mod = size % g_data.page_size;
	// if (mod == 0)
	// 	return (size);
	// return (size + g_data.page_size - mod);
}

void	*get_map(const int kind, const size_t size, size_t size_to_alloc)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	void	*map;

	(void)kind;
	(void)size;
	if (DEBUG_DPF)
		ft_dpf(2, "data mmap -> %u\n", size_to_alloc);
	map = mmap((void *)0, size_to_alloc,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	ft_dpf(2, "%smmap()%s -> %p\n", "\033[36m", "\033[0m", map);
	if (DEBUG_DPF)
		ft_dpf(2, "%smap address%s -> %p\n", "\033[36m", "\033[0m", map);
	return (map);
}

int		vote_nako(void)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	int		page_size;

	if ((page_size = getpagesize()) <= 0 || (page_size % 8) != 0)
		return (-1);
	g_data.page_size = page_size;
	g_data.nako.size = page_size * 3;
	return (0);
}

int		vote_yena(void)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	int		page_size;

	if ((page_size = getpagesize()) <= 0 || (page_size % 8) != 0)
		return (-1);
	g_data.page_size = page_size;
	g_data.yena.size = page_size * 9;
	if (DEBUG_DPF)
		ft_dpf(2, "     page size -> %u\n", g_data.page_size);
	if (DEBUG_DPF)
		ft_dpf(2, "yena page size -> %u\n", g_data.yena.size);
	return (0);
}

int		vote_wonyoung(void)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	int		page_size;

	if ((page_size = getpagesize()) <= 0 || (page_size % 8) != 0)
		return (-1);
	g_data.page_size = page_size;
	return (0);
}

void	select_nako(void *map, const size_t size_map)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem				*member;
	static const size_t	block_size = sizeof(t_ch) + TINY_SIZE;
	void				*minju;
	void				*minju_dooooo;
	t_ch				*ptr;
	register size_t		idx;
	register size_t		max_iteration;
	void				*end;

	member = (t_mem *)map;
	member->bk = (t_mem *)0;
	member->fd = (t_mem *)0;
	member->size = size_map;
	member->kind = TINY;
	member->fill = 0;
	// member->user = (t_ch *)(((void *)member)
	// 			+ ((sizeof(void *) * 2 + sizeof(size_t) * 2)));
	minju = ((void *)member) + (sizeof(t_mem));
	idx = 0;
	max_iteration = (size_map - (sizeof(t_mem))) / block_size;
	if (DEBUG_DPF)
		ft_dpf(2, "max iteration -> %u\n", max_iteration);
	if (DEBUG_DPF)
		ft_dpf(2, "block size ---> %u\n", block_size);

	ft_dpf(2, "size_map   == %u\n", size_map);
	ft_dpf(2, "map            == [%u]\n", map);
	ft_dpf(2, "map + size_map == [%u]\n", map + size_map);
	// minju_dooooo = minju;
	minju_dooooo = map;
	end = map + size_map;
	ft_dpf(2, "minju_dooooo [%p]\n", minju_dooooo);
	ft_dpf(2, "end          [%p]\n", end);
	ft_dpf(2, "diff hehe    [%u]\n", end - minju_dooooo);
	// while (idx < max_iteration)
	while (minju_dooooo + block_size < end)
	{
		if (DEBUG_DPF)
			ft_dpf(2, "[%u] < [%u]\n", idx, max_iteration);
		if (DEBUG_DPF)
			ft_dpf(2, "  map address: %p\n", member);
		minju_dooooo = minju + block_size;
		ptr = (t_ch *)minju;
		if (DEBUG_DPF)
			ft_dpf(2, "  bich: [%p]\n", ptr);
		if (DEBUG_DPF)
			ft_dpf(2, "  hello: [%p]\n", minju_dooooo);
		ptr->used = UNUSED;
		ptr->fill[0] = 0;
		ptr->fill[1] = 0;
		ptr->fill[2] = 0;
		ptr->kind = TINY;
		ptr->fd = (t_ch *)minju_dooooo;
		minju += (block_size);
		++idx;
	}
	ft_dpf(2, "map:        [%p] size map -> [%u]\n", map, size_map);
	ft_dpf(2, "end select: [%p]\n", ((void *)ptr) + block_size);
	ft_dpf(2, "final:      [%p]\n", map + size_map);
	ft_dpf(2, "diff:       [%p]\n", (map + size_map - (void *)ptr));
	ptr->fd = (t_ch *)0;
}

void	select_yena(void *map, const size_t size_map)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem				*member;
	static const size_t	block_size = sizeof(t_ch) + SMALL_SIZE;
	void				*minju;
	void				*minju_dooooo;
	t_ch				*ptr;
	register size_t		idx;
	register size_t		max_iteration;
	void				*end;

	member = (t_mem *)map;
	member->bk = (t_mem *)0;
	member->fd = (t_mem *)0;
	member->size = size_map;
	member->kind = SMALL;
	member->fill = 0;
	// member->user = (t_ch *)(((void *)member)
	// 			+ ((sizeof(t_mem))));
	minju = ((void *)member) + (sizeof(t_mem));
	idx = 0;
	max_iteration = (size_map - (sizeof(t_mem))) / block_size;
	if (DEBUG_DPF)
		ft_dpf(2, "max iteration -> %u\n", max_iteration);
	if (DEBUG_DPF)
		ft_dpf(2, "block size ---> %u\n", block_size);
	// minju_dooooo = minju;
	minju_dooooo = map;
	end = map + size_map;
	// while (idx < max_iteration)
	while (minju_dooooo + block_size < end)
	{
		if (DEBUG_DPF)
			ft_dpf(2, "[%u] < [%u]\n", idx, max_iteration);
		if (DEBUG_DPF)
			ft_dpf(2, "  map address: %p\n", member);
		minju_dooooo = minju + block_size;
		ptr = (t_ch *)minju;
		if (DEBUG_DPF)
			ft_dpf(2, "  bich: [%p]\n", ptr);
		if (DEBUG_DPF)
			ft_dpf(2, "  hello: [%p]\n", minju_dooooo);
		ptr->used = UNUSED;
		ptr->fill[0] = 0;
		ptr->fill[1] = 0;
		ptr->fill[2] = 0;
		ptr->kind = SMALL;
		ptr->fd = (t_ch *)minju_dooooo;
		minju += (block_size);
		++idx;
	}
	ft_dpf(2, "map:        [%p] size map -> [%u]\n", map, size_map);
	ft_dpf(2, "end select: [%p]\n", ((void *)ptr) + block_size);
	ft_dpf(2, "final:      [%p]\n", map + size_map);
	ft_dpf(2, "diff:       [%p]\n", (end - (void *)ptr));
	ptr->fd = (t_ch *)0;
}

void	select_wonyoung(void *map, const size_t size_map)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem	*member;
	t_ch	*ptr;

	member = (t_mem *)map;
	member->bk = (t_mem *)0;
	member->fd = (t_mem *)0;
	member->size = size_map;
	member->kind = LARGE;
	member->fill = 0;
	// member->user->fd = (t_ch *)0;
	ptr = ((void *)member
			+ (sizeof(t_mem)));
	ptr->fill[0] = 0;
	ptr->fill[1] = 0;
	ptr->fill[2] = 0;
	ptr->fd = (t_ch *)0;
	ptr->kind = LARGE;
	ptr->used = UNUSED;
	// member->user->fill = 0;
	// member->user->used = UNUSED;
}

int		init_data(const int kind, const size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	static int	(*vote_izone[SIZE_KIND])(void) = {
		[TINY] = &vote_nako,
		[SMALL] = &vote_yena,
		[LARGE] = &vote_wonyoung
	};
	static size_t	(*get_size_to_alloc[SIZE_KIND])(size_t) = {
		[TINY] = &get_nako_size_map,
		[SMALL] = &get_yena_size_map,
		[LARGE] = &get_wonyoung_size_map
	};
	static void	(*select_izone_members[SIZE_KIND])(void *, const size_t) = {
		[TINY] = &select_nako,
		[SMALL] = &select_yena,
		[LARGE] = &select_wonyoung
	};
	size_t		size_to_alloc;

	void	*map;

	if (vote_izone[kind]() == -1)
		return (-1);
	size_to_alloc = get_size_to_alloc[kind](size);
	if ((map = get_map((const int)kind, size,
				(const size_t)size_to_alloc)) == (void *)0)
	{
		if (DEBUG_DPF)
			ft_dpf(2, "%smap failed !%s\n", "\033[31m", "\033[0m");
		return (-1);
	} else {
		if (DEBUG_DPF)
			ft_dpf(2, "%smap success !%s\n", "\033[32m", "\033[0m");
	}
	select_izone_members[kind](map, size_to_alloc);
	g_data.izone[kind].map = map;
	return (0);
}

void	*get_nako(__attribute__((__unused__))size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem	*minju;
	t_ch	*minju_doooo;

	minju = g_data.nako.map;
	while (minju != (t_mem *)0)
	{
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "La la la la vie en rose !\n");
		minju_doooo = (t_ch *)(((void *)minju)
				+ ((sizeof(t_mem))));
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "  wollah minju doooooo -> %p\n", minju_doooo);
		while (minju_doooo->fd != (t_ch *)0)
		{
			// if (DEBUG_DPF)
			// 	ft_dpf(2, "  minju doooooo -> %p\n", minju_doooo);
			if (minju_doooo->used == UNUSED)
			{
				if (DEBUG_DPF)
					ft_dpf(2, "    %sViolata !%s %p\n", "\033[35m", "\033[0m", minju_doooo);
				minju_doooo->used = USED;
				return (((void *)minju_doooo) + sizeof(t_ch));
			}
			minju_doooo = minju_doooo->fd;
		}
		minju = minju->fd;
	}
	return ((void *)0);
}

void	*get_yena(__attribute__((__unused__))size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem	*minju;
	t_ch	*minju_doooo;

	minju = g_data.yena.map;
	while (minju != (t_mem *)0)
	{
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "La la la la vie en rose !\n");
		minju_doooo = (t_ch *)(((void *)minju)
				+ ((sizeof(t_mem))));
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "  wollah minju doooooo -> %p\n", minju_doooo);
		while (minju_doooo->fd != (t_ch *)0)
		{
			// if (DEBUG_DPF)
			// 	ft_dpf(2, "  minju doooooo -> %p\n", minju_doooo);
			if (minju_doooo->used == UNUSED)
			{
				if (DEBUG_DPF)
					ft_dpf(2, "    %sViolata !%s %p\n", "\033[35m", "\033[0m", minju_doooo);
				minju_doooo->used = USED;
				return (((void *)minju_doooo) + sizeof(t_ch));
			}
			minju_doooo = minju_doooo->fd;
		}
		minju = minju->fd;
	}
	return ((void *)0);
}

void	*get_wonyoung(size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	t_mem	*minju;
	t_ch	*minju_doooo;

	minju = g_data.wonyoung.map;
	if (DEBUG_DPF)
		ft_dpf(2, "size allocation wanted from user --> %u\n", size);
	while (minju != (t_mem *)0)
	{
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "jpp de ma vie___\n");
		minju_doooo = (t_ch *)(((void *)minju)
				+ (sizeof(t_mem)));
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "used ? %d -> size %u\n", minju_doooo->used, minju->size);
		if (minju_doooo->used == UNUSED && size <= minju->size)
		{
			minju_doooo->used = USED;
			// if (DEBUG_DPF)
			// 	ft_dpf(2, "in ah in ah in artist baby\n");
			return (((void *)minju_doooo) + sizeof(t_ch));
		}
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "jpp de ma vie___2222\n");
		minju = minju->fd;
	}
	if (DEBUG_DPF)
		ft_dpf(2, "============= MDR WHAT\n");
	return ((void *)0);
}

void	append_mem(const int kind, void *violeta, const size_t size_map)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	// t_mem	*la_vie_en_rose;

	// la_vie_en_rose = (t_mem *)violeta;
	// la_vie_en_rose->bk = (t_mem *)0;
	// la_vie_en_rose->fd = (t_mem *)0;
	// la_vie_en_rose->fill = 0;
	// la_vie_en_rose->kind = kind;
	// la_vie_en_rose->size = size_map;
	static void	(*select_izone_members[SIZE_KIND])(void *, size_t) = {
		[TINY] = &select_nako,
		[SMALL] = &select_yena,
		[LARGE] = &select_wonyoung
	};
	t_mem	*ptr;
	t_mem	*new;

	select_izone_members[kind](violeta, size_map);
	ptr = (t_mem *)g_data.izone[kind].map;
	new = (t_mem *)violeta;
	// if (DEBUG_DPF)
	// 	ft_dpf(2, "ptr %s------>%s %p\n", "\033[34m", "\033[0m", (void *)ptr);
	while (ptr->fd != (t_mem *)0)
	{
		ptr = ptr->fd;
		// if (DEBUG_DPF)
		// 	ft_dpf(2, "ptr %s------>%s %p\n", "\033[34m", "\033[0m",(void *)ptr);
	}
	if (DEBUG_DPF)
		ft_dpf(2, "ptr %s-->%s %p\n", "\033[34m", "\033[0m", (void *)ptr);
	if (DEBUG_DPF)
		ft_dpf(2, "new %s-->%s %p\n", "\033[34m", "\033[0m", (void *)new);
	ptr->fd = new;
	new->bk = ptr;
}

void	*get_user_mem(const int kind, size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	static void 	*(*get_mem[SIZE_KIND])(size_t) = {
		[TINY] = &get_nako,
		[SMALL] = &get_yena,
		[LARGE] = &get_wonyoung
	};
	static size_t	(*get_size_to_alloc[SIZE_KIND])(size_t) = {
		[TINY] = &get_nako_size_map,
		[SMALL] = &get_yena_size_map,
		[LARGE] = &get_wonyoung_size_map
	};
	void	*res;
	void	*violeta;
	size_t	size_map;
	int		retry;

	if (kind == NONE)
		return ((void *)0);
	retry = 10;
	res = (void *)0;
	size_map = get_size_to_alloc[kind](size);
	while (retry > 0 && (res = get_mem[kind](size)) == (void *)0)
	{
		if ((violeta = get_map(kind, size, size_map)) != (void *)0)
			append_mem(kind, violeta, size_map);
		--retry;
	}
	// if (res)
		// ft_memset(res, 'a', 1);
	if (DEBUG_DPF)
		ft_dpf(2, "==== RESULT MALLOC: %p\n", res);
	return (res);
}

void	*malloc(size_t size)
{
	if (DEBUG_DPF)
		ft_dpf(2, "\n%s:%s%s%s:%d\n", __FILE__, "\033[31m", __func__, "\033[0m", __LINE__);
	// void	*mem;
	// size_t	*ptr;
	int		kind;

	kind = get_area_kind_by_size((const size_t)size);
	if (kind == NONE
			|| (g_data.izone[kind].map == (t_mem *)0
					&& init_data(kind, size) == -1))
		return ((void *)0);
	return (get_user_mem((const int)kind, size));
}

// mem = mmap(0, size + sizeof(size_t), PROT_READ | PROT_WRITE,
// 		MAP_ANON | MAP_PRIVATE, -1, 0);
// ptr = (size_t *)mem;
// *ptr = size;
// return (mem + sizeof(size_t));
