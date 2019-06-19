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

// typedef struct	s_chunk
// {
// 	size_t			prev_size;
// 	size_t			size;
// 	struct s_chunk	*fd;
// 	struct s_chunk	*bk;
// 	// user mem
// }				t_chunk;

typedef struct	s_ch
{
	_Bool		used; // padding (need only 1 bit)
	_Bool		fill[3];
	int			kind;
    struct s_ch	*fd;
    // void		*p; // user
}				t_ch;

typedef struct	s_mem
{
	struct s_mem	*bk;
    struct s_mem	*fd;
	size_t			size;
	int				kind;
	int				fill;
    // t_ch			*user;
    // void			*user;
}				t_mem;

typedef struct	s_area
{
	t_mem	*map; // map list
    size_t	size; // size map const for tiny and small
}				t_area;

typedef struct	s_meta
{
	union {
		struct {
			t_area	nako;
			t_area	yena;
			t_area	wonyoung;
		};
		t_area		izone[3]; // IZ*ONE HWAITING
	};
	int				page_size;
}				t_meta;

// typedef struct	s_meta
// {
//     t_area	nako;
//     t_area	yena;
//     t_area	wonyoung;
//     int		page_size;
// 	int		is_init;
// }				t_meta;

extern t_meta	g_data;

#endif
