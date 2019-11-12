#include "ft_malloc_int.h"

#include "utils.h"
t_chunk	*find_chunk_by_user_mem(void *ptr)
{
	PRINT_FILE();
	t_area	*izone;
	t_chunk	*cur;
	_Bool	*is_used;
	int		idx;
	int		jdx;

	izone = g_mdata.izone;
	idx = 0;
	while (idx < SIZE_KIND)
	{
		cur = izone[idx].root;
		while (cur != NULL)
		{
			is_used = (_Bool *)(cur + 1);
			jdx = 0;
			while (jdx < izone[idx].length)
			{
				if (is_used[jdx]
						&& (cur->user_pool + jdx * izone[idx].size) == ptr)
					return (cur);
				++jdx;
			}
			cur = cur->next;
		}
		++idx;
	}
	return (NULL);
}

t_chunk	*find_chunk_idx_by_user_mem(void *ptr, int *index)
{
	PRINT_FILE();
	t_area	*izone;
	t_chunk	*cur;
	_Bool	*is_used;
	int		idx;

	izone = g_mdata.izone;
	idx = 0;
	*index= -1;
	while (idx < SIZE_KIND)
	{
		cur = izone[idx].root;
		while (cur != NULL)
		{
			is_used = (_Bool *)(cur + 1);
			*index = 0;
			while ((*index) < izone[idx].length)
			{
				if (is_used[*index]
						&& (cur->user_pool + (*index) * izone[idx].size) == ptr)
					return (cur);
				++(*index);
			}
			cur = cur->next;
		}
		++idx;
	}
	*index = -1;
	return (NULL);
}
