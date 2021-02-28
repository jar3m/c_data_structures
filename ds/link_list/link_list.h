#pragma once
#include "common.h"



typedef enum {
	eSINGLE_LINKLIST,
	eDOUBLE_LINKLIST,
	eCIRCULAR_LINKLIST,
}e_lltype;

typedef struct elem {
	int data;
	struct elem *nxt;
	struct elem *prv;
} t_elem;


typedef struct linklist {
	e_lltype type;

	int count;
	t_elem *head;
	t_elem *tail;
} t_linklist;


//API
#if 0
t_data create_link_list(e_lltype type); //me
destroy_link_list(t_data); //me
add_link_list(t_data, int);	//rang
del_link_list(t_data, int);//rang	
get_elem(t_data, int);	//may
index(data)	//may
count	//rang
swap	//rang
reverse//may
print //me
#endif
