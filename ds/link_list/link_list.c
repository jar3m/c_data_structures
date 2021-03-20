#include "link_list.h"

void add_end_sll(t_data d,int data);
void add_end_dll(t_data d,int data);
void add_end_scll(t_data d,int data); 
void add_end_dcll(t_data d,int data);

f_append append[] = {add_end_sll,add_end_dll,add_end_scll,add_end_dcll};

/*
 *
 * */
t_data create_link_list (char *name, e_lltype type)
{
	t_linklist *l = (t_linklist*)get_mem(1, sizeof(t_linklist));

	l->name = name;
	l->type = type;
	l->count = 0;
	l->tail = l->head = NULL;
	l->append = append[type];
	
	return (t_data)l;
}


/*
 *
 * */
void add_end_sll(t_data d,int data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	node->nxt = NULL;
	node->data = data;
	l->count++;
	if (l->head == NULL) {
		l->head = node;
	} else {
		l->tail->nxt = node;
	}
	l->tail = node;
}

/*
 *
 * */
void add_end_dll(t_data d,int data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	node->prv = node->nxt = NULL;
	node->data = data;
	l->count++;
	if (l->head == NULL) {
		l->head = node;
	} else {
		node->prv = l->tail;
		l->tail->nxt = node;
	}
	l->tail = node;
}

/*
 *
 * */
void add_end_scll(t_data d,int data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	node->nxt = NULL;
	node->data = data;
	l->count++;
	if (l->head == NULL) {
		l->head = node;
	} else {
		l->tail->nxt = node;
	}
	l->tail = node;
	l->tail->nxt = l->head;
}

/*
 *
 * */
void add_end_dcll(t_data d,int data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	node->nxt = NULL;
	node->data = data;
	l->count++;
	if (l->head == NULL) {
		l->head = node;
	} else {
		l->tail->nxt = node;
		node->prv = l->tail;
	}
	l->head->prv = l->tail = node;
	l->tail->nxt = l->head;
}

/*
 *
 * */
void destroy_link_list (t_data d)
{	
	t_linklist *l = (t_linklist*)d;
	t_elem *tmp,*ptr;
	int i;

	ptr = l->head;
	// delete all node in llist
	for (i = 0; i < l->count; i++) {
		if (ptr == NULL) {
			LOG_ERROR(l->name, "%d nodes still remain\n", l->count - i);
			break;
		}
		tmp = ptr;	
		ptr = ptr->nxt;
		// free node
		tmp->nxt = tmp->prv = NULL;
		free_mem(tmp);	
	}


	l->count = 0;
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
	int i;

	printf("%s [",l->name);
	for (i = 0; i < l->count; i++) {
		printf(" %d", ptr->data);
//		printf("[ %u %d %u]", ptr->prv, ptr->data, ptr->nxt);
		ptr = ptr->nxt;
	}
	printf(" ]\n");

}
