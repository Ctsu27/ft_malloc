#ifndef FT_MALLOC_INT_H
# define FT_MALLOC_INT_H

# include <sys/types.h>

# define DEBUG_DPF 0
# define DEPLOY_DPF 1

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

# define TINY_SIZE		64
# define SMALL_SIZE		512

struct	s_dlst
{
	struct s_dlst	*bk;
	struct s_dlst	*fd;
};

typedef struct s_dlst t_dlst;

typedef struct	s_area
{
	struct s_area	*bk;
	struct s_area	*fd;
	size_t			size_map;
	size_t			fill;
}				t_area;

// t_area is for my meta data to stock other map for user
// after t_area: as chunks
/**
 *	void 	*user_mem; ptr of an amount of map for user
 *	size_t	size_of_portion_of_this_map;
 *	size_t	size_requested_of_user_within_this_map;
 *	size_t	is_used; // can use only 1bit instead of 32/64bit
 */

typedef struct	s_chunk
{
	void	*user_mem;
	size_t	size_chunk;
	size_t	size_user_requested;
	size_t	is_used;
}				t_chunk;

typedef struct	s_meta
{
	union {
		struct {
			t_area	*nako;
			t_area	*yena;
			t_area	*wonyoung;
		};
		t_area		*izone[SIZE_KIND]; // IZ*ONE HWAITING
	};
	int				page_size;
}				t_meta;

extern t_meta	g_mdata;

#endif
