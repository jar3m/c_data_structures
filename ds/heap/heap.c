/*! @file heap.c
    @brief 
    Contains definitions of routines supported by heap 
*/

#include "heap.h"

void heap_insert(t_gen d,t_gen data);
t_gen heap_extract_root(t_gen d);
void heap_build(t_gen d);
void heap_sort(t_gen d);
int heap_len(t_gen d);
void heap_print(t_gen d);
bool heap_empty(t_gen d);
bool heap_full(t_gen d);
t_gen heap_update_key(t_gen d, t_gen val, int idx);
void destroy_heap(t_gen d);


/*! @brief  
 *  Create an instance of heap
 *  @param name     - Name of heap instance
 *  @param size     - Max size of heap instance
 *  @param type     - Type of heap to be created
 *  @param data     - Array pointer to build heap
 *  @param prm      - Data type specific parameters
 *  @return         - Pointer to instance of heap
*/
t_gen create_heap(char *name, t_gen data, int size, e_heaptype htype, t_dparams *prm)
{
	t_heap *h = get_mem(1, sizeof(t_heap));

	// Initailze heap Params
	h->name       = name;
	h->type       = htype;
	h->data       = data;
	h->size       = size;
	h->count      = 0;
	
	// Initailze heap routines
	h->insert     = heap_insert;
	h->extract    = heap_extract_root;
	h->build      = heap_build;
	h->sort       = heap_sort;
	h->len        = heap_len;
	h->update     = heap_update_key;
	h->full	      = heap_full;
	h->empty      = heap_empty;
	h->print      = heap_print;
	h->destroy    = destroy_heap;

	// Initailze datatype based operations req for prop working of heap
	h->cmpr	      =	prm->cmpr;
	h->cmpr_idx   =	prm->cmpr_idx;
	h->swap_idx   =	prm->swap_idx; 
	h->copy_idx   =	prm->copy_idx;
	h->get_idx    =	prm->get_idx;
	h->print_data =	prm->print_data;
	
	return (t_gen)h;
}


/*! @brief  
 *  To check if heap full
 *  @param d    - Pointer to instance of heap 
 *  @return     - true if heap full
 * */
bool heap_full(t_gen d)
{
	t_heap *h = (t_heap*)d;

	return (h->count >= h->size);
}

/*! @brief  
 *  To check if heap empty
 *  @param d    - Pointer to instance of heap 
 *  @return     - true if heap empty
 * */
bool heap_empty(t_gen d)
{
	t_heap *h = (t_heap*)d;

	return (h->count == 0);
}

/*! @brief  
 *  Preserve heap property on insert
 *  by heapifying from bottom to root
 *  @param d    - Pointer to instance of heap 
 *  @param idx  - Index of node to heapify
 *  @return     - NA
 * */
void heapify_up(t_heap *h, int idx)
{
	int parent;
	e_cmpr cmp_res;
	// exit condition depending type of heap
	cmp_res = (h->type == eMAX_HEAP)? eGREAT : eLESS;

	for (parent = (idx - 1) / 2; idx; parent = (idx - 1) / 2) {
		// Heap prop satisfied parent </> child for min/max heap
		// else swap parent and child and go one up
		if (h->cmpr_idx(h->data, parent, idx) == cmp_res) {
			break;
		} else {
			h->swap_idx(h->data, parent, idx);
		}
		idx = parent;
	}
}

/*! @brief  
 *  Insert an element to heap
 *  @param d    - Pointer to instance of heap 
 *  @param data - Pointer to data that has to be added to heap
 *  @return 	- NA
 * */
void heap_insert(t_gen d,t_gen data)
{
	t_heap *h = (t_heap*)d;

	if (h->count >= h->size) {
		LOG_WARN("HEAP", "%s: HEAP_FULL\n",h->name);
		return;
	}
	
	h->copy_idx(h->data, h->count, data);
	heapify_up(h, h->count);
	h->count++;
}

/*! @brief  
 *  Rearrange a heap to maintain the heap property 
 *  aka heapyfy_down
 *  @param d    - Pointer to instance of heap 
 *  @param idx  - Index of node to heapify
 *  @return 	- NA
 */
void heapify(t_heap *h, int idx)
{
	int parent,lchild,rchild;
	e_cmpr cmp_res;
	
	// exit condition depending type of heap
	cmp_res = (h->type != eMAX_HEAP)? eGREAT : eLESS;
	lchild = rchild = 0;
	for (parent = idx; rchild <= h->count; ) {
		lchild = (2 * idx)+1; rchild = (2 * parent) + 2;
		// Heap prop satisfied parent </> child for min/max heap
		// else parent and child and go one up
		if (lchild < h->count && h->cmpr_idx
				(h->data, parent, lchild) == cmp_res) {
			parent = lchild;
		}
		if (rchild < h->count && h->cmpr_idx
				(h->data, parent, rchild) == cmp_res) {
			parent = rchild;
		}
	
		// if parent has changed swap parent with idx
		if (idx != parent) {
			h->swap_idx(h->data, parent, idx);
			idx = parent;
		} else {
			break;
		}
	}	
}

/*! @brief  
 *  Build a heap given a array
 *  @param d    - Pointer to instance of heap 
 *  @return 	- NA
 */
void heap_build(t_gen d)
{
	t_heap *h = (t_heap*)d;
	int idx;
	
	h->count = h->size;
	for(idx = h->size/2; idx >= 0; idx--) {
		heapify(h, idx);
	}
}


/*! @brief  
 *  Extract the root from heap
 *  @param d    - Pointer to instance of heap 
 *  @return 	- Pointer to extracted root node element of heap
 */
t_gen heap_extract_root(t_gen d)
{
	t_heap *h = (t_heap*)d;
	t_gen data = NULL;

	if (h->count == 0) {
		LOG_WARN("HEAP", "%s: HEAP EMPTY\n",h->name);
		return data;
	}
	
	// Root is swapped with last node in heap
	// temp store root at last heap location
	h->count--;
	h->swap_idx(h->data, 0, h->count);

	// heapify to preserve heap prop
	heapify(h, 0);
	
	//Ref to previous heap root is returned
	data = h->get_idx(h->data, h->count);
	
	return data;
}

/*! @brief  
 *  Heap sort the data
 *  @param d    - Pointer to instance of heap 
 *  @return 	- NA
 */
void heap_sort(t_gen d)
{
	t_heap *h = (t_heap*)d;
	int i,n = (h->count-1);
	
	// build heap
	h->build(h);

	// Move the current root to last
	// sorted but in traverse in reverse order
	for(;h->count;) {
		// Root to be deleted is swapped with last node in heap
		h->count--;
		h->swap_idx(h->data, 0, h->count);
		// heapify to preserve heap prop
		heapify(h, 0);
	}
}

/*! @brief  
 *  heap update value of given node
 *  @param d    - Pointer to instance of heap 
 *  @param val  - Pointer of value to be copied to given heap node
 *  @param idx  - Node idx of heap to which value has to be updated
 *		  idx b/w 0 and heap node count -1
 *  @return 	- Pointer to updated node data
 */
t_gen heap_update_key(t_gen d, t_gen val, int idx)
{
	t_heap *h = (t_heap*)d;
	t_gen tmp = NULL;
	e_cmpr cmp_res;
	
	if (idx < 0 || idx >= h->count) {
		LOG_WARN("HEAP", "%s: idx out of bound\n",h->name);
		return tmp;
	}

	// exit condition depending type of heap
	cmp_res = (h->type != eMAX_HEAP)? eGREAT : eLESS;
	tmp = h->get_idx(h->data, idx);
	
	// If new val '<'/'>' previous val or min/max heap
	// then heapify up else heapify down
	if (h->cmpr(tmp, val) == cmp_res) {
		h->copy_idx(h->data, idx, val);
		heapify_up(h, idx);
	}
	else {
		h->copy_idx(h->data, idx, val);
		heapify(h, idx);
	}

	return tmp;
}

/*! @brief  
 *  heap count
 *  @param d    - Pointer to instance of heap 
 *  @return 	- heap length
 */
int heap_len(t_gen h)
{
	return ((t_heap*)h)->count;
}

/*! @brief  
 *  Destroy the instance of the heap
 *  @param d    - Pointer to instance of heap 
 *  @return 	- NA
 */
void destroy_heap(t_gen d)
{
	t_heap *h = (t_heap*)d;
	
	free_mem(h);
}

/*  @brief
 *  Util function to get type of heap in string
 *  @param type  - heap Type
 *  @return String of heap type
*/
char * get_heaptype_name(e_heaptype type)
{
	switch (type) {
		case eMIN_HEAP:
			return "MIN_HEAP";
		case eMAX_HEAP:
			return "MAX_HEAP";
	}

	return "UNDEFINED";
}
/*! @brief  
 *  heap_print_info
 *  @param d    - Pointer to instance of heap 
 *  @return 	- NA
*/
void heap_print(t_gen d)
{
	t_heap *h = (t_heap*)d; 
	int i;

	printf("%s:%s {count: %d} {size: %d}\n[ ",h->name, 
			get_heaptype_name(h->type), h->count, h->size);
	for (i = 0; i < h->size; i ++) {
		h->print_data(h->get_idx(h->data, i));
		printf(" ");
	}
	printf("]\n");
}
