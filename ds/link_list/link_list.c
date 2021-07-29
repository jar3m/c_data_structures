/*! @file link_list.c
    @brief 
    Contains definitions of routines supported by link list
*/

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
t_gen del_node_xor_idx(t_gen d, int idx);

int linklist_length(t_gen d);
t_gen linklist_find(t_gen d, t_gen data);
t_gen linklist_getnode(t_gen d, int idx);

void linklist_print (t_gen d);
void linklist_print_info (t_gen d);

void destroy_link_list (t_gen d);

t_gen linklist_get_head(t_gen);
t_gen linklist_get_tail(t_gen);
t_gen linklist_get_end(t_gen);
t_gen linklist_get_next(t_gen, t_gen);
t_gen linklist_get_prev(t_gen, t_gen);
t_gen linklist_get_node_data(t_gen);

t_gen xor(t_gen x, t_gen y);

/// Look Up function ptrs for add based on type of list
f_ins add[] = {add_begin_sll,add_begin_dll,add_begin_scll,add_begin_dcll, add_begin_xor_dll};

/// Look Up function ptrs for apend (add end) based on type of list
f_ins append[] = {add_end_sll,add_end_dll,add_end_scll,add_end_dcll, add_end_xor_dll};

/// Look Up function ptrs for delete node based on type of list
f_del del[] = {del_node_sll, del_node_dll, del_node_scll, del_node_dcll, del_node_xor_dll};

/// Look Up function ptrs for delete ith node based on type of list
f_del_idx del_idx[] = {del_node_sll_idx, del_node_dll_idx, del_node_scll_idx, del_node_dcll_idx, del_node_xor_idx};

/*! @brief  
 *  Create an instance of link list
 *  @param name - Name of link list instance
 *  @param type - Type of link list to be created
 *  @param prm  - Data type specific parameters
 *  @return     - Pointer to instance of link list 
 * */
t_gen create_link_list (char *name, e_lltype type, t_dparams *prm)
{
	t_linklist *l = (t_linklist*)get_mem(1, sizeof(t_linklist));
	
	// Initailze LL Params
	l->name  = name;
	l->type  = type;
	l->count = 0;
	l->tail  = l->head = NULL;

	// Select Functions based on type of list
	l->append   	 = append[type];
	l->add      	 = add[type];
	l->del      	 = del[type];
	l->del_idx  	 = del_idx[type];
	l->get_idx  	 = linklist_getnode;
	l->len 	    	 = linklist_length;
	l->find     	 = linklist_find;
	l->head_node	 = linklist_get_head;
	l->tail_node	 = linklist_get_tail;
	l->end_node 	 = linklist_get_end;
	l->next_node	 = linklist_get_next;
	l->prev_node	 = linklist_get_prev;
	l->destroy  	 = destroy_link_list;
	l->print    	 = linklist_print;
	l->print_info    = linklist_print_info;
	l->get_node_data = linklist_get_node_data;

	l->cmpr      	 = prm->cmpr;
	l->swap      	 = prm->swap;
	l->print_data	 = prm->print_data;
	l->free      	 = prm->free;

	return (t_gen)l;
}

/*! @brief  
 *  Fetch node data;
 *  @param data - Pointer to the node whose data to fetch
 *  @return 	- Node data
 */
t_gen linklist_get_node_data(t_gen n)
{
	t_llnode *node = (t_llnode*)n;
	
	return node->data;
}

/*! @brief  
 *  Add Beggining for singly LL
 *  @param d    - Pointer to instance of link list 
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_begin_sll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	
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

/*! @brief  
 *  Add Beggining for doubly LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_begin_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	
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

/*! @brief  
 *  Add Beggining for Singly Circular LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_begin_scll(t_gen d,t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));

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

/*! @brief  
 *  Add Beggining for Doubly Circular LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 **/
void add_begin_dcll(t_gen d,t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));

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

/*! @brief  
*   Util fuction to complete xor operation between two pointers
*   returns the xor'ed result as a t_gen type
* */
t_gen xor(t_gen x, t_gen y) 
{
	return (t_gen)((uintptr_t)(x) ^ (uintptr_t)(y));
}

/*! @brief  
 *   Add begin in xor link list
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_begin_xor_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node;
	
	// create node and store data
	node = (t_llnode*)get_mem(1, sizeof(t_llnode));
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

/*! @brief  
 *  Add End for Singly LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_end_sll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	
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

/*! @brief  
 *  Add End for Doublly LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_end_dll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	
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
  
/*! @brief  
 *  Add End for Singly Circular LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_end_scll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	
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

/*! @brief  
 *  Add End for Doubly Circular LL
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_end_dcll(t_gen d,t_gen data) 
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	
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

/*! @brief  
 *   add end in xor link list
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data to be added
 *  @return 	- NA
 * */
void add_end_xor_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node;

	// Create a node and assign data
	node = (t_llnode*)get_mem(1, sizeof(t_llnode));
	node->data = data;
	
	// node->nxt = l->tail ^ NULL;
	node->nxt = xor(l->tail, NULL);

	if (l->head == NULL) {
		// List Empty upadte head 
		//l->head = (t_llnode *)XOR(node, l->head) ;
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

/*! @brief  
 *   Delete node with matching data in singly LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data which has to be deleted
 *  @return 	- Pointer to the data
 * */
t_gen del_node_sll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head, *prv;
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



/*! @brief  
 *   Delete node with matching data in Doublly LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data which has to be deleted
 *  @return 	- Pointer to the data
 * */
t_gen del_node_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head;
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



/*! @brief  
 *   Delete node with matching data in Singly Circular LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data which has to be deleted
 *  @return 	- Pointer to the data
 * */
t_gen del_node_scll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head, *prv;
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



/*! @brief  
 *   Delete node with matching data in Doubly Circular LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data which has to be deleted
 *  @return 	- Pointer to the data
 * */
t_gen del_node_dcll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head;
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

/*! @brief  
*   Delete node with matching data in xor link list
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer of data for the node to be deleted
 *  @return 	- Pointer to the data of the deleted node
* */
t_gen del_node_xor_dll(t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head;
	t_llnode *prev = NULL , *next = NULL;
	t_gen tmp = NULL;


	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	// Head node is to be deleted and new head is updated
	if (l->cmpr(cur->data, data) == eEQUAL) {
		// l->head = cur->nxt ^ prev;
		l->head = xor(cur->nxt, prev);

		// update reverse link
		// Reset Tail to NULL if list empty
		if (l->head != NULL) {
			l->head->nxt = xor(prev, xor(l->head->nxt, cur));
		}
		else {
			l->tail = NULL;
		}

		l->count--;
		// Free node
		tmp = cur->data;
		cur->nxt =  NULL;
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

	// next = cur->nxt ^ prev;
	next = xor(cur->nxt, prev);

	// prev->nxt = (prev->nxt ^ cur) ^ (next) ;
	prev->nxt = xor(next, xor(prev->nxt, cur)) ;

	// Update tail when the last node is deleted
	if (next == NULL) {
		l->tail = prev;
	}
	else {
		// next->nxt = (next->nxt ^ cur) ^ prev;
		next->nxt = xor(prev, xor(next->nxt, cur));
	}
	
	// free node
	l->count --;
	tmp = cur->data;
	cur->nxt = NULL; 
	free_mem(cur);

	return tmp;

}


/*! @brief  
 *   Delete node with matching index in singly LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param idx  - index of the node to be deleted
 *  @return 	- Pointer to the data of the deleted node
 * */
t_gen del_node_sll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head, *prv = NULL;
	t_gen tmp = NULL;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}
	// idx >count
	if (idx >= l->count && idx < 0) {
		LOG_WARN("LINK_LIST", "%d: Index out of bounds, number of nodes that exist = %d\n",idx, l->count);
		return tmp;
	}

	for(int i = 0; i < idx; i++) {
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



/*! @brief  
 *   Delete node with matching index  in Doublly LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param idx  - index of the node to be deleted
 *  @return 	- Pointer to the data of the deleted node
 * */
t_gen del_node_dll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head;
	t_gen tmp = NULL;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}

	// idx >list count
	if (idx >= l->count && idx < 0) {
		LOG_WARN("LINK_LIST", "%d: Index out of bounds, number of nodes that exist = %d\n",idx, l->count);
		return tmp;
	}

	for(int i = 0; i < idx ; i ++) {
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


/*! @brief  
 *   Delete node with matching index in Singly Circular LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param idx  - index of the node to be deleted
 *  @return 	- Pointer to the data of the deleted node
 * */
t_gen del_node_scll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head, *prv;
	t_gen tmp = NULL;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}
	// idx >list count
	if (idx >= l->count && idx < 0) {
		LOG_WARN("LINK_LIST", "%d: Index out of bounds, number of nodes that exist = %d\n",idx, l->count);
		return tmp;
	}

	for(int i = 0; i < idx; i ++) {
		prv = cur;
		cur = cur->nxt;

		// Node to be deleted not found
		if (cur == l->head) {
			LOG_INFO("LINK_LIST", "%s: No node of index %d found within the link list\n",l->name, idx);
			return tmp;
		}
	}

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

	else {
		// Unlink cur node and update fwd link
		prv->nxt = cur->nxt;
		// If last node deleted update tail ref
		if (prv->nxt == l->head) {
			l->tail = prv;
		}
	}

	// Free node
	l->count--;
	cur->nxt = NULL;
	tmp = cur->data;
	free_mem(cur);

	return tmp;
}

/*! @brief  
 *   Delete node with matching index in Doubly Circular LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param idx  - index of the node to be deleted
 *  @return 	- Pointer to the data of the deleted node
 * */
t_gen del_node_dcll_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head;
	t_gen tmp;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}
	
	// idx > list count
	if (idx >= l->count && idx < 0) {
	  LOG_WARN("LINK_LIST", "%d: Index out of bounds, number of nodes that exist = %d\n",idx, l->count);
		return tmp;
	}

	for(int i = 0; i < idx; i ++) {
		cur = cur->nxt;
		if(cur == l->head) {
			LOG_INFO("LINK_LIST", "%s: No node of index %d found within the link list\n",l->name, idx);
			return tmp;
		}
	}

	// Head node is to be deleted and new head is updated
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

	else {
	  // Unlink cur node and update fwd 
	  cur->prv->nxt = cur->nxt;
	  if (cur->nxt == l->head) {
		  // If last node deleted update tail ref
		  l->head->prv = l->tail = cur->prv;
	  } else {
		  cur->nxt->prv = cur->prv;
	  }
	}

	l->count--;
	// Free node
	cur->nxt = cur->prv = NULL;
	tmp = cur->data;
	free_mem(cur);
	
	return tmp;

}

/*! @brief  
 *   Delete node with matching index in XOR LL
 *   and return the instance
 *  @param d    - Pointer to instance of link list
 *  @param idx  - index of the node to be deleted
 *  @return 	- Pointer to the data of the deleted node
 * */
t_gen del_node_xor_idx(t_gen d, int idx)
{
	t_linklist *l = (t_linklist *)d;
	t_llnode *cur = l->head, *prv = NULL, *next = NULL;
	t_gen tmp = NULL;

	// empty list
	if (l->head == NULL) {
		LOG_WARN("LINK_LIST", "%s: No nodes exist\n",l->name);
		return tmp;
	}
	// idx >count
	if (idx >= l->count && idx < 0) {
		LOG_WARN("LINK_LIST", "%d: Index out of bounds, number of nodes that exist = %d\n",idx, l->count);
		return tmp;
	}


	for(int i = 0; i < idx; i++) {
		prv = cur;
		cur = l->next_node(l, prv);
	}
  
	// delete for head node
	if (idx == 0) {
	
		// l->head = cur->nxt ^ prev;
		l->head = xor(cur->nxt, prv);

		// update reverse link
		// Reset Tail to NULL if list empty
		if (l->head != NULL) {
			l->head->nxt = xor(prv, xor(l->head->nxt, cur));
		}
		else {
			l->tail = NULL;
		}

	}
  // delete for all the other nodes apart from head
	else {
		// next = cur->nxt ^ prev;
		next = xor(cur->nxt, prv);

		// prev->nxt = (prev->nxt ^ cur) ^ (next) ;
		prv->nxt = xor(next, xor(prv->nxt, cur)) ;

		// Update tail when the last node is deleted
		if (next == NULL) {
			l->tail = prv;
		}
		else {
			// next->nxt = (next->nxt ^ cur) ^ prev;
			next->nxt = xor(prv, xor(next->nxt, cur));
		}
	}
  l->count--;
  // Free node
  tmp = cur->data;
  cur->nxt =  NULL;
  free_mem(cur);

	return tmp;
	
}


/*! @brief  
 *   Length of the link list
 *  @param d    - Pointer to instance of link list
 *  @return 	- length of link list
 * */
int linklist_length(t_gen d)
{
	t_linklist *l = (t_linklist*)d;

	return l->count;
}

/*! @brief 
 *   Get the i th node of the link list
 *   idx of node should be between 0 and < list count
 *  @param d    - Pointer to instance of link list
 *  @param idx  - idx, (0 <= idx < list count)
 *  @return 	- Pointer to node
 * */
t_gen linklist_getnode(t_gen d, int idx)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *ptr;
	int i;	

	// return NULL for index out of bound
	if ((idx < 0) || (idx >= l->count)) {
		return NULL;
	}
	ptr = l->head_node(l);
	
	for (i = 0; i < idx; i++) {
		ptr = l->next_node(l, ptr);
	}

	return ptr;
}

/*! \brief Brief description.
 *   Find data in the link list
 *  @param d    - Pointer to instance of link list
 *  @param data - Pointer to the data
 *  @return 	- Pointer of the node
 * */
t_gen linklist_find (t_gen d, t_gen data)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *ptr, *end;
	
	ptr = l->head_node(l);
	// if empty list, return NULL
	if (ptr == NULL) {
		return NULL;
	}
	
	end = l->end_node(l);
	
	while (l->cmpr(ptr->data, data) != eEQUAL) {
		ptr = l->next_node(l, ptr);

		//reach end of the linked list and node not present, return NULL
		if (ptr == end) {
			return NULL;
		}
	}

        return ptr;
}


/*! @brief  
 *   Get the head node of link list
 *  @param d    - Pointer to instance of link list 
 *  @return 	- Head Node pointer
 * */
t_gen linklist_get_head(t_gen d)
{
	t_linklist *l = (t_linklist*)d;

	return l->head;
}

/*! @brief  
 *   Get the tail node of link list
 *  @param d    - Pointer to instance of link list 
 *  @return 	- Tail Node pointer
 * */
t_gen linklist_get_tail(t_gen d)
{
	t_linklist *l = (t_linklist*)d;

	return l->tail;
}

/*! @brief  
 *   Get the end of link list
 *  @param d    - Pointer to instance of link list 
 *  @return 	- End Node pointer
 * */
t_gen linklist_get_end(t_gen d)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *end = NULL;

	// Return end of link list depending on type of link list
	switch (l->type)
	{
		case eSINGLE_LINKLIST:
		case eDOUBLE_LINKLIST:
			end = NULL;
			break;
		case eSINGLE_CIRCULAR_LINKLIST:
		case eDOUBLE_CIRCULAR_LINKLIST:
			end = l->head;
			break;
		case eXOR_LINKLIST:
			end = NULL;
			break;
	}
	return end;
}

/*! @brief  
 *   Get the next node of given node in link list
 *   limitation for xor next node be it iterrates from head
 *   meaning first call should pass head node addr 
 *   and next time next node and so on
 *  @param d    - Pointer to instance of link list 
 *  @param n    - Pointer to node whose next node is returned
 *  @return 	- Next Node pointer
 * */
t_gen linklist_get_next(t_gen d, t_gen n)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *node = (t_llnode*)n, *next;
	static t_llnode *prev = NULL;

	// return node -> next except for xor list
	if (l->type != eXOR_LINKLIST) {
		return node->nxt;
	}
	// limitation for xor next node be it iterrates from head
	// meaning first call should pass head node addr 
	// and next time next node and so on
	prev = (l->head == node)? NULL: prev;
	next = xor(node->nxt, prev);
	prev = node;

	return next;
}

/*! @brief  
 *   Get the prev node of given node in link list
 *   limitation for xor prev node be it iterrates from tail
 *   meaning first call should pass tail node addr 
 *   and next time the node before tail and so on
 *  @param d    - Pointer to instance of link list 
 *  @param n    - Pointer to node whose prev node is returned
 *  @return 	- Prev Node pointer
 * */
t_gen linklist_get_prev(t_gen d, t_gen n)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *prev = NULL, *node = (t_llnode*)n;
	static t_llnode *next = NULL;

	// Return end of link list depending on type of link list
	switch (l->type)
	{
		case eSINGLE_LINKLIST:
		case eSINGLE_CIRCULAR_LINKLIST:
			prev = NULL;
			break;
		case eDOUBLE_LINKLIST:
		case eDOUBLE_CIRCULAR_LINKLIST:
			prev = node->prv;
			break;
		case eXOR_LINKLIST:
			// XOR node previous work only on reverse traveersal
			// meaning first call should pass tail node addr 
			// and next time the node before tail and so on
			next = (l->tail == node)? NULL: next;
			prev = xor(node->nxt, next);
			next = node;
			break;
	}
	

	return prev;
}

/*  @brief
 *  Util function to get type of list in string
 *  @param type  - Link list Type
 *  @return String of link list type
*/
char * get_lltype_name(e_lltype type)
{
	switch(type) {
		case eSINGLE_LINKLIST:
			return "SINGLE_LINKLIST";
		case eDOUBLE_LINKLIST:
			return "DOUBLE_LINKLIST";
		case eSINGLE_CIRCULAR_LINKLIST:
			return "SINGLE_CIRCULAR_LINKLIST";
		case eDOUBLE_CIRCULAR_LINKLIST:
			return "DOUBLE_CIRCULAR_LINKLIST";
		case eXOR_LINKLIST:
			return "XOR_LINKLIST";
	}

	return "UNDEFINED";
}

/*! @brief  
 *   Print the elems of link list
 *  @param d    - Pointer to instance of link list 
 *  @return 	- NA
 * */
void linklist_print (t_gen d)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *ptr, *end;
	int i;

	printf("%s : [", l->name);

	// get head ptr of ll
	ptr = l->head_node(l);
	// exit for Circ or non circ linked list
	end = l->end_node(l);

	while (ptr) {
		l->print_data(ptr->data);
		printf(" ");
		ptr = l->next_node(l, ptr);

		// exit if end of list
		if (ptr == end) {
			break;
		}
	}
	printf("]\n");

}


/*! @brief  
 *   Print the elem in linklist with linkinfo
 *  @param d    - Pointer to instance of link list 
 *  @return 	- NA
 * */
void linklist_print_info (t_gen d)
{
	t_linklist *l = (t_linklist*)d;
	t_llnode *ptr, *end;
	int i;

	printf("%s:%s {Head: %lx} {Tail: %lx} {count: %u}\n[",l->name,
			get_lltype_name(l->type),(long)l->head,(long)l->tail, l->count);

	// get head of link list
	ptr = l->head_node(l);
	// exit for Circ or non circ linked list
	end = l->end_node(l);

	while (ptr) {
		printf("[ %lx ", (long)ptr->prv);
		l->print_data(ptr->data);
		printf(" %lx]", (long)ptr->nxt);
	
		ptr = l->next_node(l, ptr);
		// exit if end of list
		if (ptr == end) {
			break;
		}
	}
	printf(" ]\n");

}


/*! @brief  
 *   Destroy instance of the LL
 *  @param d    - Pointer to instance of link list 
 *  @return 	- NA
 * */
void destroy_link_list (t_gen d)
{	
	t_linklist *l = (t_linklist*)d;
	t_llnode *tmp,*ptr,*end;
	int i;

	// delete all node in llist
	ptr = l->head_node(l);

	// exit for Circ or non circ linked list
	end = l->end_node(l);

	while (ptr) {
		tmp = ptr;	
		ptr = l->next_node(l, ptr);
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


