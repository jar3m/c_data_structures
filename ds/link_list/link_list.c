#include "link_list.h"

void add_begin_sll(t_data d,int data);
void add_begin_dll(t_data d,int data);
void add_begin_scll(t_data d,int data); 
void add_begin_dcll(t_data d,int data);

void add_end_sll(t_data d,int data);
void add_end_dll(t_data d,int data);
void add_end_scll(t_data d,int data); 
void add_end_dcll(t_data d,int data);

void del_node_sll(t_data d, int data);
void del_node_dll(t_data d, int data);
void del_node_scll(t_data d, int data); 
void del_node_dcll(t_data d, int data);

f_add add[] = {add_begin_sll,add_begin_dll,add_begin_scll,add_begin_dcll};
f_append append[] = {add_end_sll,add_end_dll,add_end_scll,add_end_dcll};
f_del del[] = {del_node_sll, del_node_dll, del_node_scll, del_node_dcll};

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
	l->add = add[type];
	l->del = del[type];
	
	return (t_data)l;
}

void add_begin_sll(t_data d, int data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	l->count++;	
	node->data = data;
	node->nxt = l->head; 
	
	l->head = node;
}

/*
 *
 * */
void add_begin_dll(t_data d, int data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	l->count++;	
	node->data = data;
	node->nxt = l->head;
	node->prv = NULL;
	if(l->head != NULL) {
		l->head->prv = node;
	}
	l->head = node;
}

/*
 *
 * */
void add_begin_scll(t_data d,int data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));

	l->count++;	
	node->data = data;
	node->nxt = l->head;
	l->head = node;
	if(l->tail != NULL) {
		l->tail->nxt = l->head;
	}else {	
		l->tail = l->head;
	}
}

void add_begin_dcll(t_data d,int data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));

	l->count++;
	node->data = data;
	node->nxt = l->head;
	node->prv = l->tail;
	if(l->tail != NULL) {
		l->head->prv = node;
		l->head = node;
		l->tail->nxt = l->head;
	}	else {
		l->tail = l->head = node ;
	}
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
void del_node_sll(t_data d, int data)
{
	t_linklist *l = (t_linklist *)d;
	if (l->head == NULL) {
	  LOG_WARN("LINK_LIST", "No nodes exist\n");
		return;
	}
	t_elem *cur = l->head, *prv;

	if (cur->data == data) {
	  printf("first node del %p, %d, %p\n", cur, cur->data, cur->nxt);
	  l->head = cur->nxt;
		cur->nxt = NULL;
		free_mem(cur);
	  l->count--;
		return;
	}

	while (cur != NULL && cur->data != data) {
	  printf("while loop %p, %d\n", cur, cur->data);
	  prv = cur;
	  cur = cur->nxt;
	}
	if (cur == NULL) {
	  LOG_INFO("LINK_LIST", "No node %d found within the link list\n", data);
	  return;
	}


	prv->nxt = cur->nxt;
	cur->nxt = NULL;
	free_mem(cur);
	l->count--;
	if (prv->nxt == NULL) {
	   l->tail = prv;
	}
	
}



/*
 *
 * */
void del_node_dll(t_data d, int data)
{
	t_linklist *l = (t_linklist *)d;
	if (l->head == NULL) {
	  LOG_WARN("LINK_LIST", "No nodes exist\n");
		return;
	}
	t_elem *cur = l->head;

	if (cur->data == data) {
	  printf("first node  dll del %p, %d, %p, %p\n", cur, cur->data, cur->nxt, cur->prv);
	  l->head = cur->nxt;
		if (l->head != NULL) {
		 l->head->prv = NULL;
		}
		cur->nxt = cur->prv = NULL;
		free_mem(cur);
	  l->count--;
		return;
	}

	while (cur != NULL && cur->data != data) {
	  cur = cur->nxt;
	}
  
  if(cur == NULL) {
	  LOG_INFO("LINK_LIST", "No node %d found within the link list\n", data);
	  return;
	}
	  

	cur->prv->nxt = cur->nxt;
	if (cur->nxt == NULL) {
	  l->tail = cur->prv;
	} else {
	  cur->nxt->prv = cur->prv;
	}
	
	cur->nxt = cur->prv = NULL;
	free_mem(cur);
	l->count--;

}



/*
 *
 * */
void del_node_scll(t_data d, int data)
{
	t_linklist *l = (t_linklist *)d;
	if (l->head == NULL) {
	  LOG_WARN("LINK_LIST", "No curs exist\n");
		return;
	}
	t_elem *cur = l->head, *prv;

	if (cur->data == data) {
	  printf("first node  scll del %p, %d, %p\n", cur, cur->data, cur->nxt);
	  l->head = cur->nxt;
		l->tail->nxt = l->head;
		cur->nxt = NULL;
		free_mem(cur);
	  l->count--;
		return;
	}

	while (cur->data != data) {
	  prv = cur;
	  cur = cur->nxt;
    if(cur == l->head) {
	    LOG_INFO("LINK_LIST", "No node %d found within the link list\n", data);
	    return;
	  }
	}
	
	prv->nxt = cur->nxt;
	cur->nxt = NULL;
	free_mem(cur);
	l->count--;
	if (prv->nxt == l->head) {
	   l->tail = prv;
	}

}



/*
 *
 * */
void del_node_dcll(t_data d, int data)
{
	t_linklist *l = (t_linklist *)d;
	if (l->head == NULL) {
	  LOG_WARN("LINK_LIST", "No nodes exist\n");
		return;
	}
	t_elem *cur = l->head;

	if (cur->data == data) {
	  printf("first node  dcll del %p, %d, %p, %p\n", cur, cur->data, cur->nxt, cur->prv);
	  l->head = cur->nxt;
		l->head->prv = l->tail;
		l->tail->nxt = l->head;
		cur->nxt = cur->prv = NULL;
		free_mem(cur);
		l->count--;
		return;
	}

	while (cur->data != data) {
	  cur = cur->nxt;
    if(cur == l->head) {
	    LOG_INFO("LINK_LIST", "No node %d found within the link list\n", data);
	    return;
	  }
	}
  

	cur->prv->nxt = cur->nxt;
	if (cur->nxt == l->head) {
	  l->tail = cur->prv;
		l->head->prv = l->tail;
	} else {
	  cur->nxt->prv = cur->prv;
	}
	
	cur->nxt = cur->prv = NULL;
	free_mem(cur);
	l->count--;

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
