#pragma once 
#include "common.h"

typedef enum {
	eMIN_HEAP,
	eMAX_HEAP,
} e_heaptype;

typedef void (*f_hins) (t_gen , t_gen);
typedef t_gen (*f_hdel) (t_gen);
typedef void (*f_hbuild) (t_gen);
typedef void (*f_hsort) (t_gen);

typedef struct heap {
	char *name;
	t_gen *data;
	
	int count;
	int size;
	e_heaptype type;
	
	f_hins insert;
	f_hdel del;
	f_hbuild build;
	f_hsort sort;
	f_cmp_idx cmpr_idx;
	f_cpy_idx copy_idx;
	f_swp_idx swap_idx;
	f_get_idx get_idx;
}t_heap;

t_gen create_heap(char *name, t_gen data,int size, e_heaptype htype, e_data_types dtype);

void destroy_heap(t_gen);
