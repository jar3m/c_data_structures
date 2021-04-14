 #include "link_list.h"

void add_begin_sll(t_gen d,t_gen data);
void add_begin_dll(t_gen d,t_gen data);
void add_begin_scll(t_gen d,t_gen data); 
void add_begin_dcll(t_gen d,t_gen data);

void add_end_sll(t_gen d,t_gen data);
void add_end_dll(t_gen d,t_gen data);
void add_end_scll(t_gen d,t_gen data); 
void add_end_dcll(t_gen d,t_gen data);

t_gen del_node_sll(t_gen d, t_gen data);
t_gen del_node_dll(t_gen d, t_gen data);
t_gen del_node_scll(t_gen d, t_gen data); 
t_gen del_node_dcll(t_gen d, t_gen data);

int len_of_link_list(t_gen d);
void print_link_list (t_gen d);

/// Look Up function call for add, append and del depending on type of list
f_add add[] = {add_begin_sll,add_begin_dll,add_begin_scll,add_begin_dcll};
f_append append[] = {add_end_sll,add_end_dll,add_end_scll,add_end_dcll};
f_del del[] = {del_node_sll, del_node_dll, del_node_scll, del_node_dcll};

/*! \brief Brief description.
 *  Create an instance of link list
 * */
t_gen create_link_list (char *name, e_lltype type, e_data_types data_type)
{
	t_linklist *l = (t_linklist*)get_mem(1, sizeof(t_linklist));
	
	// Initailze LL Params
	l->name = name;
	l->type = type;
	l->count = 0;
	l->tail = l->head = NULL;

	// Select Functions based on type of list
	l->append = append[type];
	l->add = add[type];
	l->del = del[type];
	l->len = len_of_link_list;
	l->print = print_link_list;
	switch(data_type)
	{
		case eINT8:
			//char list;
			l->cmpr = compare_char;
			l->swap = swap_char;
			l->free = FREE_MEM;
			break;
		case eINT32:
			//int list;
			l->cmpr = compare_int;
			l->swap = swap_int;
			l->free = FREE_MEM;
			break;
		case eFLOAT:
			//float list;
			l->cmpr = compare_float;
			l->swap = swap_float;
			l->free = FREE_MEM;
			break;
		case eSTRING:
			//string list;
			l->cmpr = compare_string;
			l->swap = swap_string;
			l->free = FREE_MEM;
			break;
	}
	return (t_gen)l;
}

/*! \brief Brief description.
 *  Add Beggining for singly LL
 * */
void add_begin_sll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	// Create a node and assign data
	node->data = data;
	
	// Link cur head to new node
	node->nxt = l->head; 
	
	// update tail
	if (l->head == NULL) {
		l->tail = node;
	}
	// Update head to new node
	l->head = node;
	l->count++;	
}

/*! \brief Brief description.
 *  Add Beggining for doubly LL
 * */
void add_begin_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	// Create a node and assign data
	node->data = data;

	// Link cur head to new node
	node->nxt = l->head;
	
	// ground head for head node
	node->prv = NULL;

	// Update Prv node link if non empty list
	if (l->head != NULL) {
		l->head->prv = node;
	} else {
		l->tail = node;
	}

	// Update head to new node
	l->head = node;
	l->count++;	
}

/*! \brief Brief description.
 *  Add Beggining for Singly Circular LL
 * */
void add_begin_scll(t_gen d,t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));

	// Create a node and assign data
	node->data = data;

	// Link cur head to new node
	node->nxt = l->head;

	// Update head to new node
	l->head = node;

	if (l->tail != NULL) {
		// Circ Link tail to head 
		l->tail->nxt = l->head;
	} else {	
		// List Empty update head & tail
		l->tail = l->head;
	}
	l->count++;	
}

/*! \brief Brief description.
 *  Add Beggining for Doubly Circular LL
 **/
void add_begin_dcll(t_gen d,t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));

	// Create a node and assign data
	node->data = data;

	// Circ Link new node prv & nxt with tail and head respect 
	node->nxt = l->head;
	node->prv = l->tail;

	if (l->tail != NULL) {
		// Rvrs link cur head to new node(head)
		l->head->prv = node;
		l->head = node;
		// Circ Link tail to head 
		l->tail->nxt = l->head;
	} else {
		// List Empty update head & tail
		l->tail = l->head = node ;
	}
	l->count++;
}

/*! \brief Brief description.
 *  Add End for Singly LL
 * */
void add_end_sll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	// Create a node and assign data
	node->data = data;
	node->nxt = NULL;
	
	if (l->head == NULL) {
		// List Empty upadte head 
		l->head = node;
	} else {
		// Add new node as nxt of cur tail
		l->tail->nxt = node;
	}
	// Add new node as tail
	l->tail = node;
	l->count++;
}

/*! \brief Brief description.
 *  Add End for Doublly LL
 * */
void add_end_dll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	// Create a node and assign data
	node->data = data;
	node->prv = node->nxt = NULL;

	if (l->head == NULL) {
		// List Empty upadte head 
		l->head = node;
	} else {
		// Rev link to cur tail
		node->prv = l->tail;
		// Add new node as nxt of cur tail
		l->tail->nxt = node;
	}
	// Add new node as tail
	l->tail = node;
	l->count++;
}
  
/*! \brief Brief description.
 *  Add End for Singly Circular LL
 * */
void add_end_scll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	// Create a node and assign data
	node->data = data;
	node->nxt = NULL;
	
	if (l->head == NULL) {
		// List Empty upadte head 
		l->head = node;
	} else {
		// Add new node as nxt of cur tail
		l->tail->nxt = node;
	}
	// Add new node as tail
	l->tail = node;
	// Circular link tail to head
	l->tail->nxt = l->head;
	l->count++;
}

/*! \brief Brief description.
 *  Add End for Doubly Circular LL
 * */
void add_end_dcll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
	
	// Create a node and assign data
	node->data = data;
	node->prv = node->nxt = NULL;

	if (l->head == NULL) {
		// List Empty upadte head 
		l->head = node;
	} else {
		l->tail->nxt = node;
		node->prv = l->tail;
	}
	// Add new node as tail
	// Rev link head to new tail
	l->head->prv = l->tail = node;
	// Circular link tail to head
	l->tail->nxt = l->head;
	l->count++;
}

/*! \brief Brief description.
 *   Destroy instance of the LL
 * */
void destroy_link_list (t_gen d)
{	
	t_linklist *l = (t_linklist*)d;
	t_elem *tmp,*ptr,*end;
	int i;

	// delete all node in llist
	ptr = l->head;

	end = l->tail? l->tail->nxt :l->tail;

	while (ptr) {
		tmp = ptr;	
		ptr = ptr->nxt;
		l->count--;
		// free node
		tmp->nxt = tmp->prv = NULL;
		l->free(tmp->data, __FILE__, __LINE__);
		free_mem(tmp);	
		if(ptr == end) {
			break;
		}
	}
	
	if (l->count != 0) {
		LOG_ERROR(l->name, "%d nodes remain\n", l->count);
	}
	// Reset count, head and tail ptrs
	l->tail = l->head  = NULL;

	free_mem(l);
}


/*! \brief Brief description.
 *   Delete node with matching data in singly LL
 *   and return the instance
 * */
t_gen del_node_sll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head, *prv;
	t_gen tmp = NULL;
	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}
	
	// Head node is to be deleted and new head is updated
	if (l->cmpr(cur->data, data) == eEQUAL) {
		l->head = cur->nxt;
		cur->nxt = NULL;
		tmp = cur->data;
		free_mem(cur);
		l->count--;
		// Reset Tail to NULL if list empty
		l->tail = l->head? l->tail : NULL;
		return tmp;
	}

	// Find the node to be deleted
	while (l->cmpr(cur->data, data) != eEQUAL) {
		prv = cur;
		cur = cur->nxt;
		// Node to be deleted not found
		if (cur == NULL) {
			LOG_INFO("LINK_LIST", "%s: No node %d found within the link list\n",l->name, data);
			return tmp;
		}
	}
	
	// Unlink cur node and update link
	prv->nxt = cur->nxt;
	// If last node deleted update tail ref
	if (prv->nxt == NULL) {
		l->tail = prv;
	}
	l->count--;
	// Free node
	cur->nxt = NULL;
	tmp = cur->data;
	free_mem(cur);

	return tmp;
}



/*! \brief Brief description.
 *   Delete node with matching data in Doublly LL
 *   and return the instance
 * */
t_gen del_node_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head;
	t_gen tmp = NULL;
	
	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	// Head node is to be deleted and new head is updated
	if (l->cmpr(cur->data, data) == eEQUAL) {
		l->head = cur->nxt;
		if (l->head != NULL) {
			l->head->prv = NULL;
		}
		l->count--;
		// Reset Tail to NULL if list empty
		l->tail = l->head? l->tail : NULL;
		cur->nxt = cur->prv = NULL;
		tmp = cur->data;
		free_mem(cur);
		return tmp;
	}

	// Find the node to be deleted
	while (l->cmpr(cur->data, data) != eEQUAL) {
		cur = cur->nxt;
		// Node to be deleted not found
		if(cur == NULL) {
			LOG_INFO("LINK_LIST", "%s: No node %d found within the link list\n",l->name, data);
			return tmp;
		}
	}

	// Unlink cur node and update fwd link
	cur->prv->nxt = cur->nxt;
	if (cur->nxt == NULL) {
		// If last node deleted update tail ref
		l->tail = cur->prv;
	} else {
		// Preserve rev link
		cur->nxt->prv = cur->prv;
	}

	// Free node
	l->count--;
	cur->nxt = cur->prv = NULL;
	tmp = cur->data;
	free_mem(cur);

	return tmp;
}



/*! \brief Brief description.
 *   Delete node with matching data in Singly Circular LL
 *   and return the instance
 * */
t_gen del_node_scll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head, *prv;
	t_gen tmp = NULL;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	// Head node is to be deleted and new head is updated
	if (l->cmpr(cur->data, data) == eEQUAL) {
		// Unlink cur node and update fwd link for tail
		l->tail->nxt = l->head = cur->nxt;
		l->count--;
		// Reset Tail to NULL if list empty
		if (l->count == 0) {
			l->tail = l->head = NULL;
		}
		cur->nxt = NULL;
		tmp = cur->data;
		free_mem(cur);
		return tmp;
	}

	// Find the node to be deleted
	while (l->cmpr(cur->data, data) != eEQUAL) {
		prv = cur;
		cur = cur->nxt;

		// Node to be deleted not found
		if (cur == l->head) {
			LOG_INFO("LINK_LIST", "%s: No node %d found within the link list\n",l->name, data);
			return tmp;
		}
	}

	l->count--;
	// Unlink cur node and update fwd link
	prv->nxt = cur->nxt;
	// If last node deleted update tail ref
	if (prv->nxt == l->head) {
		l->tail = prv;
	}
	// Free node
	cur->nxt = NULL;
	tmp = cur->data;
	free_mem(cur);

	return tmp;
}



/*! \brief Brief description.
 *   Delete node with matching data in Doubly Circular LL
 *   and return the instance
 * */
t_gen del_node_dcll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head;
	t_gen tmp;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	// Head node is to be deleted and new head is updated
	if (l->cmpr(cur->data, data) == eEQUAL) {
		l->head = cur->nxt;
		// Unlink cur node and update fwd and rev link
		l->head->prv = l->tail;
		l->tail->nxt = l->head;
		l->count--;
		// Reset Tail to NULL if list empty
		if (l->count == 0) {
			l->tail = l->head = NULL;
		}
		cur->nxt = cur->prv = NULL;
		tmp = cur->data;
		free_mem(cur);
		return tmp;
	}

	// Find the node to be deleted
	while (l->cmpr(cur->data, data) != eEQUAL) {
		cur = cur->nxt;
		if(cur == l->head) {
			LOG_INFO("LINK_LIST", "%s: No node %d found within the link list\n",l->name, data);
			return tmp;
		}
	}


	// Unlink cur node and update fwd 
	cur->prv->nxt = cur->nxt;
	if (cur->nxt == l->head) {
		// If last node deleted update tail ref
		l->head->prv = l->tail = cur->prv;
	} else {
		cur->nxt->prv = cur->prv;
	}

	l->count--;
	// Free node
	cur->nxt = cur->prv = NULL;
	tmp = cur->data;
	free_mem(cur);
	return tmp;
}

/*! \brief Brief description.
 *   Delete node with matching data in Doubly Circular LL
 * */
int len_of_link_list(t_gen d)
{
	t_linklist *l = (t_linklist*)d;

	return l->count;
}

/*! \brief Brief description.
 *   Delete node with matching data in Doubly Circular LL
 * */
void print_link_list (t_gen d)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *ptr = l->head, *end;
	int i;
	
	
	printf("%s {Head: %lx} {Tail: %lx} {count: %u} \n[",l->name,
			(long)l->head,(long)l->tail, l->count);
	end = l->tail? l->tail->nxt :l->tail;
	while (ptr) {
//		printf(" %d", ptr->data);
		printf("[ %lx %lx]", (long)ptr->prv, (long)ptr->nxt);
		ptr = ptr->nxt;
		if (ptr == end) {
			break;
		}
	}
	printf(" ]\n");

}
