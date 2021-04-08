#pragma once
#include "common.h"

typedef void(*f_append)(t_data,int);
typedef void(*f_add)(t_data,int);
typedef void (*f_del)(t_data, int);

typedef enum {
	eSINGLE_LINKLIST,
	eDOUBLE_LINKLIST,
	eSINGLE_CIRCULAR_LINKLIST,
	eDOUBLE_CIRCULAR_LINKLIST,
}e_lltype;

typedef struct linklist {
	char *name;
	e_lltype type;

	int count;
	t_elem *head;
	t_elem *tail;
	f_append append;
	f_add add;
	f_del del;
	f_print print;
} t_linklist;


//API
t_data create_link_list(char *name, e_lltype type); 
void destroy_link_list (t_data d);
void print_link_list (t_data d);
