#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include "ft_malloc_int.h"

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

int		append_area(t_area *area, const int kind);
void	*append_to_meta_mem_and_get_user_mem(const int kind,
		void *map, size_t size_map, size_t size_requested);
int		get_area_kind_by_size(const size_t size);
t_chunk	*get_meta_chunk_mem(const int kind);
void	*get_user_mem(const int kind, size_t size);
t_area	*new_meta_mem(void);
void	*new_user_mem(size_t size);
size_t	round_page_size(size_t size, size_t page_size);
void	*seach_available_user_mem(const int kind, size_t size);
size_t	size_align(size_t size);

t_chunk	*find_chunk_by_ptr(void *ptr);

#endif
