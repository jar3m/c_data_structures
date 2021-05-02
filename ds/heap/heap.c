#include "heap.h"

void heap_insert(t_gen d,t_gen data);
t_gen heap_delete_root(t_gen d);
void heap_build(t_gen d);
void heap_sort(t_gen d);
int heap_len(t_gen d);
void print_heap(t_gen d);

/*! \brief Brief description.
 *  Create an instance of heap
 * */
t_gen create_heap(char *name, t_gen data, int size, e_heaptype htype, e_data_types dtype)
{
	t_heap *h = get_mem(1, sizeof(t_heap));

	// Initailze heap Params
	h->name = name;
	h->type = htype;
	h->data = data;
	h->size = size;
	h->count = 0;
	
	// Initailze heap routines
	h->insert = heap_insert;
	h->del = heap_delete_root;
	h->build = heap_build;
	h->sort = heap_sort;
	h->len = heap_len;
	h->print = print_heap;

	// Initailze datatype based operations req for prop working of heap
	switch (dtype)
	{
		case eINT8:
			//char list;
			h->cmpr_idx = compare_idx_char;
			h->swap_idx = swap_idx_char;
			h->copy_idx = copy_idx_char;
			h->get_idx  = get_idx_char;
			h->print_data = print_char;
			break;
		case eINT32:
			//int list;
			h->cmpr_idx = compare_idx_int;
			h->swap_idx = swap_idx_int;
			h->copy_idx = copy_idx_int;
			h->get_idx  = get_idx_int;
			h->print_data = print_int;
			break;
		case eFLOAT:
			//float list;
			h->cmpr_idx = compare_idx_float;
			h->swap_idx = swap_idx_float;
			h->copy_idx = copy_idx_float;
			h->get_idx  = get_idx_float;
			h->print_data = print_float;
			break;

	}

	return (t_gen)h;
}

/*! \brief Brief description.
 *  Preserve heap property on insert
 *  by heapifying from bottom to root
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

/*! \brief Brief description.
 *  Insert an element to heap
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

/*! \brief Brief description.
 *  Rearrange a heap to maintain the heap property
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

/*! \brief Brief description.
 *  Build a heap given a array
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


/*! \brief Brief description.
 *  Delete the root from heap
 */
t_gen heap_delete_root(t_gen d)
{
	t_heap *h = (t_heap*)d;
	t_gen data = NULL;

	if (h->count == 0) {
		LOG_WARN("HEAP", "%s: HEAP EMPTY\n",h->name);
		return data;
	}
	
	// Root to be deleted is swapped with last node in heap
	// temp store root at last heap location
	h->count--;
	h->swap_idx(h->data, 0, h->count);
	// heapify to preserve heap prop
	heapify(h, 0);
	
	//Ref to previous heap root is returned
	data = h->get_idx(h->data, h->count);
	
	return data;
}

/*! \brief Brief description.
 *  Heap sort the data
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

/*! \brief Brief description.
 *  heap count
 */
int heap_len(t_gen h)
{
	return ((t_heap*)h)->count;
}

/*! \brief Brief description.
 *  Destroy the instance of the heap
 */
void destroy_heap(t_gen d)
{
	t_heap *h = (t_heap*)d;
	
	free_mem(h);
}

/*! \brief Brief description.
 *  print_heap_info
*/
void print_heap(t_gen d)
{
	t_heap *h = (t_heap*)d; 
	int i;

	printf("%s {count: %d} {size: %d}\n[",h->name, h->count, h->size);
	for (i = 0; i < h->size; i ++) {
		h->print_data(h->get_idx(h->data, i));
		printf(", ");
	}
	printf("]\n");
}
