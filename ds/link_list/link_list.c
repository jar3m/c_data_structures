#include "link_list.h"

/*
 *
 * */
t_data create_link_list (e_lltype type)
{
	t_linklist *l = (t_linklist*)get_mem(1, sizeof(t_linklist));

	l->type = type;
	l->count = 0;
	l->tail = l->head = NULL;
	
	return (t_data)l;
}

/*
 *
 * */
void destroy_link_list (t_data d)
{	
	t_linklist *l = (t_linklist*)d;
	t_elem *tmp,*ptr;

	ptr = l->head;
	// delete all node in llist
	while(ptr) {
		tmp = ptr;	
		ptr = ptr->nxt;
		l->count--;
		// free node
		tmp->nxt = tmp->prv = NULL;
		free_mem(tmp);	
	}

	if (l->count != 0) {
		LOG_ERROR("LINK_LIST", "%d nodes still remain\n", l->count);
	}

	l->head  = NULL;
	l->tail = NULL;

	free_mem(l);
}

/*
 *
 * */
void print_link_list (t_data d)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *ptr = l->head;

	LOG_INFO("LINKLIST", "");
	while (ptr) {
		LOG_INFO(" ","%d", ptr->data);
		ptr = ptr->nxt;
	}
	LOG_INFO(" ","\n");

}
