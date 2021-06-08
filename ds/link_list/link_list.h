#pragma once
#include "common.h"

typedef t_gen(*f_del)(t_gen, t_gen);

typedef enum {
	eSINGLE_LINKLIST,
	eDOUBLE_LINKLIST,
	eSINGLE_CIRCULAR_LINKLIST,
	eDOUBLE_CIRCULAR_LINKLIST,
	eXOR_LINKLIST,
}e_lltype;

typedef struct linklist {
	char *name;
	e_lltype type;

	int count;
	t_elem *head;
	t_elem *tail;
	
	f_ins append;
	f_ins add;
	f_del del;
	f_del_idx del_idx;
	f_len len;
	f_print print_data;
	f_cmpr cmpr;
	f_assign assign;
	f_swap swap;
	f_free free;
} t_linklist;


//API
t_gen create_link_list (char *name, e_lltype type, e_data_types data_type);
void destroy_link_list (t_gen d);
void print_link_list (t_gen d);
