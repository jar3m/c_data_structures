#include "heap.h"

void heap_insert(t_gen d,t_gen data);
t_gen heap_delete(t_gen d);
void heap_build(t_gen d);
void heap_sort(t_gen d);

t_gen create_heap(char *name, t_gen data, int size, e_heaptype htype, e_data_types dtype)
{
	t_heap *h = get_mem(1, sizeof(t_heap));

	h->name = name;
	h->type = htype;
	h->data = data;
	h->size = size;
	h->count = 0;
	
	h->insert = heap_insert;
	h->del = heap_delete;
	h->build = heap_build;
	h->sort = heap_sort;

	switch (dtype)
	{
		case eINT8:
			//char list;
			h->cmpr_idx = compare_idx_char;
			h->swap_idx = swap_idx_char;
			h->copy_idx = copy_idx_char;
			h->get_idx  = get_idx_char;
			break;
		case eINT32:
			//int list;
			h->cmpr_idx = compare_idx_int;
			h->swap_idx = swap_idx_int;
			h->copy_idx = copy_idx_int;
			h->get_idx  = get_idx_int;
			break;
		case eFLOAT:
			//float list;
			h->cmpr_idx = compare_idx_float;
			h->swap_idx = swap_idx_float;
			h->copy_idx = copy_idx_float;
			h->get_idx  = get_idx_float;
			break;

	}
}

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

void heap_insert(t_gen d,t_gen data)
{
	t_heap *h = (t_heap*)d;

	if (h->count >= h->size) {
		LOG_WARN("HEAP", "%s: HEAP_FULL\n",h->name);
		return;
	}
	
//	h->copy_idx(h->data, data, h->count);
	heapify_up(h, h->count);
	h->count++;
}

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

void heap_build(t_gen d)
{
	t_heap *h = (t_heap*)d;
	int idx;
	
	h->count = h->size;
	for(idx = h->size/2; idx >= 0; idx--) {
		heapify(h, idx);
	}
}


t_gen heap_delete(t_gen d)
{
	t_heap *h = (t_heap*)d;
	t_gen data = NULL;

	if (h->count == 0) {
		LOG_WARN("HEAP", "%s: HEAP EMPTY\n",h->name);
		return data;
	}

	h->count--;
	h->swap_idx(h->data, 0, h->count);
	heapify(h, 0);
	
	data = h->get_idx(h->data, h->count-1);
	return data;
}

void heap_sort(t_gen d)
{
	t_heap *h = (t_heap*)d;
	int i,n = (h->count-1);
	
	// build heap
	h->build(h);

	for(;h->count;) {
		h->del(h);
	}

}

void destroy_heap(t_gen d)
{
	t_heap *h = (t_heap*)d;
	
	free_mem(h);
}
