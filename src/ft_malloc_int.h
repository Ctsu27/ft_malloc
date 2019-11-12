#ifndef FT_MALLOC_INT_H
# define FT_MALLOC_INT_H

# include <stdlib.h>

# define DEBUG_DPF 0
# define DEPLOY_DPF 1

# define TINY_SIZE		64
# define SMALL_SIZE		1024

# define __CONSTRUCTOR	__attribute__((constructor)) void
# define __DESTRUCTOR	__attribute__((destructor)) void

enum	e_area_kind
{
	NONE = -1,
	TINY,
	SMALL,
	LARGE,
	SIZE_KIND
};

enum	e_memory_state
{
	UNUSED,
	USED
};

typedef struct	s_chunk
{
	struct s_chunk	*next;
	size_t			user_size;
	void			*user_pool;
}				t_chunk;

typedef struct	s_area
{
	t_chunk	*root;
	size_t	size_chunk;
	int		size;
	int		length;
}				t_area;


typedef struct	s_meta
{
	union {
		struct {
			t_area	nako;
			t_area	yena;
			t_area	wonyoung;
		};
		t_area		izone[SIZE_KIND];
	};
	int				page_size;
}				t_meta;

extern t_meta	g_mdata;

#endif
