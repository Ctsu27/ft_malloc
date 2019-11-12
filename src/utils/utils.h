#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "ft_malloc_int.h"

# define COLOR

# ifdef COLOR
#  define C_X "\033[0m"
#  define C_R "\033[31m"
#  define C_G "\033[32m"
#  define C_Y "\033[33m"
#  define C_B "\033[34m"
#  define C_P "\033[35m"
#  define C_C "\033[36m"
# else
#  define C_X ""
#  define C_R ""
#  define C_G ""
#  define C_Y ""
#  define C_B ""
#  define C_P ""
#  define C_C ""
# endif

#include "ft_printf.h"
# define DEBUG_ON 0

# define PRINT_FILE() \
		(DEBUG_ON) ? ft_dpf(2, "%scall%s --> %s%s%s() | %s%s%s:%s%d%s\n", \
			C_R, C_X, \
			C_P, __func__, C_X, \
			C_C, __FILE__, C_X, \
			C_Y, __LINE__, C_X) \
			: 0;

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

size_t	round_page_size(size_t size, size_t page_size);
size_t	size_align(size_t size);

int		get_kind(const size_t size);
t_chunk	*find_chunk_by_user_mem(void *ptr);
t_chunk	*find_chunk_idx_by_user_mem(void *ptr, int *index);

#endif
