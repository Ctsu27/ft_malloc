#include <sys/mman.h>
#include "ft_malloc_int.h"
#include "utils.h"

#include "ft_printf.h"
static inline void	*ft_map(size_t size)
{
	PRINT_FILE();
	void	*res;

	res = mmap(NULL, size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (res == MAP_FAILED)
		return (NULL);
	// ft_dpf(2, "MAP[%u] return: %p\n", size, res);
	return (res);
}

static inline void	*get_available_mem(t_chunk *mem, int offset, int length)
{
	PRINT_FILE();
	_Bool	*is_used;
	int		idx;

	if (mem == NULL)
		return (NULL);
	while (mem != NULL)
	{
		is_used = (_Bool *)(mem + 1);
		idx = 0;
		while (idx < length)
		{
			if (!is_used[idx])
			{
				is_used[idx] = 1;
				return (mem->user_pool + (idx * offset));
			}
			++idx;
		}
		mem = mem->next;
	}
	return (NULL);
}

static inline int	append_meta(t_area *kwon_eunbi, t_chunk *meta)
{
	PRINT_FILE();
	t_chunk	*cur;

	if (kwon_eunbi == NULL || meta == NULL)
		return (-1);
	if (kwon_eunbi->root == NULL)
		kwon_eunbi->root = meta;
	else
	{
		cur = kwon_eunbi->root;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = meta;
	}
	return (0);
}

static inline t_chunk	*new_meta(size_t user_size, int length)
{
	PRINT_FILE();
	t_chunk	*res;
	size_t	size;

	size = sizeof(t_chunk) + (sizeof(_Bool) * length);
	// ft_dpf(2, "size meta: %u\n", size);
	res = ft_map(size);
	if (res != NULL)
	{
		ft_memset(res, 0, size);
		res->user_size = user_size;
		if ((res->user_pool = ft_map(user_size)) == NULL)
		{
			munmap(res, size);
			res = NULL;
		}
		else
			ft_memset(res->user_pool, 0, user_size);
	}
	return (res);
}

static inline void	*kalloc(t_area *kwon_eunbi, size_t size)
{
	PRINT_FILE();
	void	*res;

	res = NULL;
	if (kwon_eunbi->root == NULL && (kwon_eunbi->root =
				new_meta(kwon_eunbi->size_chunk > 0
					? kwon_eunbi->size_chunk
					: size, kwon_eunbi->length)) == NULL)
		return (NULL);
	res = get_available_mem(kwon_eunbi->root,
			kwon_eunbi->size, kwon_eunbi->length);
	if (res == NULL)
	{
		if (append_meta(kwon_eunbi, new_meta(kwon_eunbi->size_chunk > 0
					? kwon_eunbi->size_chunk
					: size, kwon_eunbi->length)) != 0)
			return (NULL);
		else
			res = get_available_mem(kwon_eunbi->root,
					kwon_eunbi->size, kwon_eunbi->length);
	}
	return (res);
}

int		get_kind(const size_t size)
{
	PRINT_FILE();
	static const size_t	max = ((((size_t)(-1)) / 2));

	if (size <= TINY_SIZE)
		return (TINY);
	if (size <= SMALL_SIZE)
		return (SMALL);
	if (size > max)
		return (NONE);
	return (LARGE);
}

#include <unistd.h>
static int	g_init = 0;

inline static size_t	to_calcul(const int base, const int size, int *i)
{
	*i = 1;
	while ((*i) < 100 && base * (*i) / size < 100)
		++(*i);
	return (base * (*i));
}

static void	init_meta(void)
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
}

void	*malloc(size_t size)
{
	PRINT_FILE();
	int		kind;

	if (!g_init)
	{
		g_init = 1;
		init_meta();
	}
	kind = get_kind(size);
	if (kind == NONE)
		return (NULL);
	return (kalloc(&g_mdata.izone[kind], size));
}
