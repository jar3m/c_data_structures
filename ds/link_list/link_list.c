 #include "link_list.h"

void add_begin_sll(t_gen d,t_gen data);
void add_begin_dll(t_gen d,t_gen data);
void add_begin_scll(t_gen d,t_gen data); 
void add_begin_dcll(t_gen d,t_gen data);
void add_begin_xor_dll(t_gen d,t_gen data);

void add_end_sll(t_gen d,t_gen data);
void add_end_dll(t_gen d,t_gen data);
void add_end_scll(t_gen d,t_gen data); 
void add_end_dcll(t_gen d,t_gen data);
void add_end_xor_dll(t_gen d,t_gen data);

t_gen del_node_sll(t_gen d, t_gen data);
t_gen del_node_dll(t_gen d, t_gen data);
t_gen del_node_scll(t_gen d, t_gen data); 
t_gen del_node_dcll(t_gen d, t_gen data);
t_gen del_node_xor_dll(t_gen d, t_gen data);

t_gen del_node_sll_idx(t_gen d, int idx);
t_gen del_node_dll_idx(t_gen d, int idx);
t_gen del_node_scll_idx(t_gen d, int idx); 
t_gen del_node_dcll_idx(t_gen d, int idx);

int len_of_link_list(t_gen d);
void print_link_list (t_gen d);
t_gen xor(t_gen x, t_gen y);

/// Look Up function call for add, append and del depending on type of list
f_ins add[] = {add_begin_sll,add_begin_dll,add_begin_scll,add_begin_dcll, add_begin_xor_dll};
f_ins append[] = {add_end_sll,add_end_dll,add_end_scll,add_end_dcll, add_end_xor_dll};
f_del del[] = {del_node_sll, del_node_dll, del_node_scll, del_node_dcll, del_node_xor_dll};
f_del_idx del_idx[] = {del_node_sll_idx, del_node_dll_idx, del_node_scll_idx, del_node_dcll_idx};

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
	l->del_idx = del_idx[type];
	l->len = len_of_link_list;

	switch(data_type)
	{
		case eINT8:
			//char list;
			l->cmpr = compare_char;
			l->swap = swap_char;
			l->print_data = print_char;
			l->free = FREE_MEM;
			break;
		case eINT32:
			//int list;
			l->cmpr = compare_int;
			l->swap = swap_int;
			l->print_data = print_int;
			l->free = FREE_MEM;
			break;
		case eFLOAT:
			//float list;
			l->cmpr = compare_float;
			l->swap = swap_float;
			l->print_data = print_float;
			l->free = FREE_MEM;
			break;
		case eSTRING:
			//string list;
			l->cmpr = compare_string;
			l->swap = swap_string;
			l->print_data = print_str;
			l->free = FREE_MEM;
			break;
		case eGEN:
			//gen list;
			l->cmpr = compare_gen;
			l->swap = swap_gen;
			l->print_data = print_gen;
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

	// exit for Circ or non circ linked list
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
			LOG_INFO("LINK_LIST", "%s: No node found within the link list\n",l->name);
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
			LOG_INFO("LINK_LIST", "%s: No node found within the link list\n",l->name);
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
			LOG_INFO("LINK_LIST", "%s: No node found within the link list\n",l->name);
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
			LOG_INFO("LINK_LIST", "%s: No node found within the link list\n",l->name);
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
 *   Delete node with matching index in singly LL
 *   and return the instance
 * */
t_gen del_node_sll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head, *prv;
	t_gen tmp = NULL;
	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}
	if (idx >= l->count) {
	   LOG_WARN("LINK_LIST","%s: Index out of bounds\n", l->name);
		 return tmp;
	}
	
	for(int i = 0; i <= idx; i++) {
		  prv = cur;
		  cur = cur->nxt;
	}
	// Head node is to be deleted and new head is updated
	if (idx == 0) {
		l->head = cur->nxt;
		// Reset Tail to NULL if list empty
		l->tail = l->head? l->tail : NULL;
	}

  else {	
	  // Unlink cur node and update link
	  prv->nxt = cur->nxt;
	  // If last node deleted update tail ref
	  if (prv->nxt == NULL) {
		  l->tail = prv;
	  }
	}
	l->count--;
	// Free node
	cur->nxt = NULL;
	tmp = cur->data;
	free_mem(cur);

	return tmp;
}



/*! \brief Brief description.
 *   Delete node with matching index  in Doublly LL
 *   and return the instance
 * */
t_gen del_node_dll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head;
	t_gen tmp = NULL;
	
	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	for(int i = 0; i <= idx ; i ++) {
		  cur = cur->nxt;
	}
	  // Head node is to be deleted and new head is updated
	if (idx == 0) {
		l->head = cur->nxt;
		if (l->head != NULL) {
			l->head->prv = NULL;
		}
		// Reset Tail to NULL if list empty
		l->tail = l->head? l->tail : NULL;
	}


	// Unlink cur node and update fwd link
	else {
	  cur->prv->nxt = cur->nxt;
	  if (cur->nxt == NULL) {
		  // If last node deleted update tail ref
		  l->tail = cur->prv;
	  } else {
		  // Preserve rev link
		  cur->nxt->prv = cur->prv;
	  }
	}

	// Free node
	l->count--;
	cur->nxt = cur->prv = NULL;
	tmp = cur->data;
	free_mem(cur);

	return tmp;
}


/*! \brief Brief description.
 *   Delete node with matching index in Singly Circular LL
 *   and return the instance
 * */
t_gen del_node_scll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head, *prv;
	t_gen tmp = NULL;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	for(int i = 0; i <= idx && i <= l->count; i ++) {
	  // Head node is to be deleted and new head is updated
	  if (idx == 0) {
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
	  else {
		  prv = cur;
		  cur = cur->nxt;

		  // Node to be deleted not found
		  if (cur == l->head) {
			  LOG_INFO("LINK_LIST", "%s: No node of index %d found within the link list\n",l->name, idx);
			  return tmp;
		  }
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
 *   Delete node with matching index in Doubly Circular LL
 *   and return the instance
 * */
t_gen del_node_dcll_idx(t_gen d, int idx)
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
	for(int i = 0; i <= idx && i <= l->count; i ++) {
	  if (idx == 0) {
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
	  //while (l->cmpr(cur->data, data) != eEQUAL) {
		else {
		  cur = cur->nxt;
		  if(cur == l->head) {
			  LOG_INFO("LINK_LIST", "%s: No node of index %d found within the link list\n",l->name, idx);
			  return tmp;
		  }
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
 *   return the length of the link list
 * */
int len_of_link_list(t_gen d)
{
	t_linklist *l = (t_linklist*)d;

	return l->count;
}

/*! \brief Brief description.
 *   print the elements of a link list
 * */
void print_link_list (t_gen d)
{
	t_linklist *l = (t_linklist*)d;
	t_elem *ptr = l->head, *end, *prev = NULL, *cur= NULL;
	int i;

	printf("%s {Head: %lx} {Tail: %lx} {count: %u} \n[",l->name,
			(long)l->head,(long)l->tail, l->count);
	end = l->tail? l->tail->nxt :l->tail;
	while (ptr) {
		//printf("[ %lx ", (long)ptr->prv);
		//l->print_data(ptr->data);
		//printf(" %lx]", (long)ptr->nxt);
	  if(l->type == eXOR_LINKLIST) {
		  printf("[ %lx" , (long)prev);
		  l->print_data(ptr->data);
		  printf(" %lx]", (long)ptr);
		  cur = xor(ptr->nxt, prev);
			prev = ptr;
			ptr = cur;
		}
		else {
		  printf("[ %lx ", (long)ptr->prv);
		  l->print_data(ptr->data);
		  printf(" %lx]", (long)ptr->nxt);
		  ptr = ptr->nxt;
		  if (ptr == end) {
			  break;
		  }
	  }
	}
	printf(" ]\n");

}


/*! 
*   XOR function to safely complete xor operation between two pointers
*   returns the xor'ed result as a t_gen type
* */
t_gen xor(t_gen x, t_gen y) {
  return (t_gen)((uintptr_t)(x) ^ (uintptr_t)(y));
}

/*! 
*   XOR based doubly linked list
*   both links are stored in a single pointer by XOR operation
* */
void add_begin_xor_dll(t_gen d, t_gen data)
{
  t_linklist *l = (t_linklist*)d;
  t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));
  node->data = data;
  //node->nxt = l->head ^ NULL 
  node->nxt = xor(l->head ,NULL);

  if (l->head != NULL)
  {
      // In order to get the address of the next node, XOR it with `NULL`
			//l->head->nxt = (l->head->nxt ^ NULL) ^ node;
      l->head->nxt = xor(node, xor(l->head->nxt, NULL));
  }
  
  // update tail
  if (l->head == NULL) {
    l->tail = node;
  }
  // Update head to new node
  l->head = node;
  l->count++;
 
}


void add_end_xor_dll(t_gen d, t_gen data)
{
  t_linklist *l = (t_linklist*)d;
  t_elem *node = (t_elem*)get_mem(1, sizeof(t_elem));

  // Create a node and assign data
  node->data = data;
	//node->nxt = l->tail ^ NULL;
  node->nxt = xor(l->tail, NULL);

  if (l->head == NULL) {
    // List Empty upadte head 
    //l->head = (t_elem *)XOR(node, l->head) ;
		l->head = l->tail = node;
  } else {
    // Add new node as nxt of cur tail
		//l->tail->nxt = (l->tail->nxt ^ NULL) ^ node;
    l->tail->nxt = xor(node, xor(l->tail->nxt,  NULL));
  }
  // Add new node as tail
  l->tail = node;
  l->count++;
}

t_gen del_node_xor_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_elem *cur = l->head;
  t_elem *prev = NULL , *next = NULL;
	t_gen tmp = NULL;

	
	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
  }
	
	// Head node is to be deleted and new head is updated
	if (l->cmpr(cur->data, data) == eEQUAL) {
	  //l->head = cur->nxt ^ prev;
		l->head = xor(cur->nxt, prev);
		l->count--;
		// Reset Tail to NULL if list empty
		l->tail = l->head? l->tail : NULL;
		cur->nxt =  NULL;
		tmp = cur->data;
		free_mem(cur);
		return tmp;
	}

	// Find the node to be deleted
	while (l->cmpr(cur->data, data) != eEQUAL) {
	  //next = cur->nxt ^ prev;
	  next = xor(cur->nxt, prev);
		// Node to be deleted not found
		if(next == NULL) {
			LOG_INFO("LINK_LIST", "%s: No node found within the link list\n",l->name);
			return tmp;
    }
    prev = cur;
    cur = next;	
	}
  //  next = cur->nxt ^ prev;

	//  prev->nxt = (prev->nxt ^ cur) ^ (next) ;
  next = xor(cur->nxt, prev);

  prev->nxt = xor(next, xor(prev->nxt, cur)) ;

  // Update tail when the last node is deleted
  if (next == NULL) {
    l->tail = prev;
  }
  else {
	  //next->nxt = (next->nxt ^ cur) ^ prev;
    next->nxt = xor(prev, xor(next->nxt, cur));
  }
  l->count --;
  tmp = cur->data;
  cur->nxt = NULL; 
  free(cur);

	return tmp;

}

