#pragma once
#include "common.h"

typedef t_gen(*f_del)(t_gen, t_gen);

/// Type of linklists
typedef enum {
	eSINGLE_LINKLIST,
	eDOUBLE_LINKLIST,
	eSINGLE_CIRCULAR_LINKLIST,
	eDOUBLE_CIRCULAR_LINKLIST,
	eXOR_LINKLIST,
}e_lltype;

/// Link list struct definition
typedef struct linklist {
	// linklist info params
	char *name;
	e_lltype type;
	int count;

	// linklist head and tail ref
	t_elem *head;
	t_elem *tail;
	
	// linklist routines
	f_ins append;
	f_ins add;
	f_del del;
	f_destroy destroy;
	f_del_idx del_idx;
	f_len len;
	f_print print;

	// routies for operating on data
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
