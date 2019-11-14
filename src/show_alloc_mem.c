#include "ft_malloc_int.h"
#include "ft_printf.h"

static inline void	show_area(const t_area *kwon_eunbi, const int kind, int fd)
{
	static const char	*kind_str[SIZE_KIND] = {
		[TINY] = "TINY", [SMALL] = "SMALL", [LARGE] = "LARGE"
	};
	t_chunk				*minju;
	size_t				size;
	_Bool				*is_used;
	int					i;

	minju = kwon_eunbi->root;
	while (minju != NULL)
	{
		ft_dpf(fd, "%s : %p\n", kind_str[kind], minju->user_pool);
		is_used = (_Bool *)(minju + 1);
		i = 0;
		size = kwon_eunbi->size ? kwon_eunbi->size : minju->user_size;
		while (i < kwon_eunbi->length)
		{
			if (is_used[i])
				ft_dpf(fd, "%p - %p : %u bytes\n",
						minju->user_pool + (i * size),
						minju->user_pool + ((i + 1) * size), size);
			++i;
		}
		minju = minju->next;
	}
}

void				show_alloc_mem(void)
{
	t_area	*izone;
	int		idx;

	izone = g_mdata.izone;
	idx = 0;
	while (idx < SIZE_KIND)
	{
		show_area(izone + idx, idx, 1);
		++idx;
	}
}

void				show_alloc_mem_fd(int fd)
{
	t_area	*izone;
	int		idx;

	izone = g_mdata.izone;
	idx = 0;
	while (idx < SIZE_KIND)
	{
		show_area(izone + idx, idx, fd);
		++idx;
	}
}
