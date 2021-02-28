#include "common.h"

t_elem* get_node(int data)
{
	t_elem *node = (t_elem*)get_mem(sizeof(t_elem),1);

	node->data = data;
	node->nxt = node->prv = NULL;

	return node;
}

