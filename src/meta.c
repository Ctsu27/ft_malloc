#include <unistd.h>
#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

t_meta	g_mdata;

inline static size_t	to_calcul(const int base, const int size, int *i)
{
	*i = 1;
	while ((*i) < 100 && base * (*i) / size < 100)
		++(*i);
	if (*i < 128)
		*i = 128;
	return (size * (*i));
}

__CONSTRUCTOR			init_meta(void)
{
	g_mdata.page_size = getpagesize();
	g_mdata.nako.root = NULL;
	g_mdata.nako.size = TINY_SIZE;
	g_mdata.nako.size_chunk = to_calcul(g_mdata.page_size,
			TINY_SIZE, &g_mdata.nako.length);
	g_mdata.yena.root = NULL;
	g_mdata.yena.size = SMALL_SIZE;
	g_mdata.yena.size_chunk = to_calcul(g_mdata.page_size,
			SMALL_SIZE, &g_mdata.yena.length);
	g_mdata.wonyoung.root = NULL;
	g_mdata.wonyoung.size_chunk = 0;
	g_mdata.wonyoung.size = 0;
	g_mdata.wonyoung.length = 1;

	// ft_dpf(2, "nako.size: %u\n", g_mdata.nako.size);
	// ft_dpf(2, "nako.size_chunk: %u\n", g_mdata.nako.size_chunk);
	// ft_dpf(2, "nako.length: %u\n", g_mdata.nako.length);
	// ft_dpf(2, "yena.size: %u\n", g_mdata.yena.size);
	// ft_dpf(2, "yena.size_chunk: %u\n", g_mdata.yena.size_chunk);
	// ft_dpf(2, "nako.length: %u\n", g_mdata.nako.length);
	// ft_dpf(2, "wonyoung.size_chunk: %u\n", g_mdata.wonyoung.size_chunk);
	// ft_dpf(2, "wonyoung.size: %u\n", g_mdata.wonyoung.size);
	// ft_dpf(2, "wonyoung.length: %u\n", g_mdata.wonyoung.length);
}

static inline void		_delete(t_area *kwon_eunbi)
{
	t_chunk	*cur;
	t_chunk	*tmp;
	size_t	size_meta;
	size_t	size_chunk;

	size_meta = sizeof(t_chunk) + (sizeof(_Bool) * kwon_eunbi->length);
	size_chunk = kwon_eunbi->size_chunk;
	cur = kwon_eunbi->root;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		ft_memset(tmp->user_pool, 0, tmp->user_size);
		munmap(tmp->user_pool, tmp->user_size);
		munmap(tmp, size_meta);
	}
}

__DESTRUCTOR			dump_garbage(void)
{
	PRINT_FILE();
	t_area	*izone;
	int		idx;

	izone = g_mdata.izone;
	idx = 0;
	while (idx < SIZE_KIND)
	{
		_delete(izone + idx);
		++idx;
	}
}
