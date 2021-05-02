#include "tree.h"
#include "queue.h"

void tree_insert_node(t_gen,t_gen);
t_gen tree_delete_node(t_gen,t_gen);
t_gen tree_find_node(t_gen,t_gen);
t_gen tree_node_predecessor(t_gen,t_gen);
t_gen tree_node_successor(t_gen,t_gen);
t_gen tree_get_min(t_gen);
t_gen tree_get_max(t_gen);
void print_tree(t_gen);

/*! \brief Brief description.
 *  Create an instance of tree
 * */
t_gen create_tree(char *name, e_treetype ttype, e_data_types dtype)
{
	t_tree *t = get_mem(1, sizeof(t_tree));

	// Initailze tree Params
	t->name = name;
	t->type = ttype;
	t->count = 0;
	t->root = NULL;
	
	// Initailze tree routines
	t->insert = tree_insert_node;
	t->del = tree_delete_node;
	t->find = tree_find_node;
	t->predcessor = tree_node_predecessor;
	t->successor = tree_node_successor;
	t->min = tree_get_min;
	t->max = tree_get_max;
	t->print = print_tree;

	// Initailze datatype based operations req for prop working of tree
	switch(dtype)
	{
		case eINT8:
			//char tree;
			t->cmpr = compare_char;
			t->swap = swap_char;
			t->free = FREE_MEM;
			t->print_data = print_char;
			break;
		case eINT32:
			//int tree;
			t->cmpr = compare_int;
			t->swap = swap_int;
			t->free = FREE_MEM;
			t->print_data = print_int;
			break;
		case eFLOAT:
			//float tree;
			t->cmpr = compare_float;
			t->swap = swap_float;
			t->free = FREE_MEM;
			t->print_data = print_float;
			break;
		case eSTRING:
			//string tree;
			t->cmpr = compare_string;
			t->swap = swap_string;
			t->free = FREE_MEM;
			t->print_data = print_str;
			break;
	}

	return (t_gen)t;
}

/*! \brief Brief description.
 *   Add element to tree
 */
void tree_insert_node(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *new = get_mem(1, sizeof(t_tree_node));
	t_tree_node *parent = NULL, *cur;
	e_cmpr res;

	// Create Node and add data
	new->key = data;
	new->lchild = new->rchild = NULL;
	
	// tree is empty
	if (t->root == NULL) {
		t->root = new;
		return;
	}

	cur = t->root;
	// get position in tree to insert node
	while (cur != NULL) {
		parent = cur;
		// if new node < cur node 
		// new node to be inserted in left subtree
		// else insert in right subtree
		res = t->cmpr(new->key, cur->key);
		if (res == eLESS) {
			cur = cur->lchild;
		} else {
			cur = cur->rchild;
		}
	}
	
	// If the new key is less then the leaf node key
	// Assign the new node to be its left child
	// else Assign the new node to be its right child
	res = t->cmpr(new->key, parent->key);
	if (res == eLESS) {
		parent->lchild = new;
	} else {
		parent->rchild = new;
	}
}

/*! \brief Brief description.
 *   find an element in tree
 */
t_gen tree_find_node(t_gen d, t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur;
	e_cmpr res;
	
	cur = t->root;
	while (cur != NULL) {
		// if new node < cur node 
		// node to be searched in left subtree
		// else search in right subtree
		res = t->cmpr(data, cur->key);
		if (res == eEQUAL) {
			break;
		} else if (res == eLESS) {
			cur = cur->lchild;
		} else {
			cur = cur->rchild;
		}
	}

	// return NULL if not found else node
	return cur;
}

/*! \brief Brief description.
 *  get min node in tree 
 */
t_gen tree_get_min(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur;
	
	// tree is empty
	if (t->root == NULL) {
		return NULL;
	}

	// left most node contains min
	cur = t->root;
	while (cur->lchild != NULL) {
		cur = cur->lchild;
	}

	return cur->key;
}

/*! \brief Brief description.
 *  get max node in tree 
 */
t_gen tree_get_max(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur;
	
	// tree is empty
	if (t->root == NULL) {
		return NULL;
	}

	// right most node contains min
	cur = t->root;
	while (cur->rchild != NULL) {
		cur = cur->rchild;
	}

	return cur->key;
}

/*! \brief Brief description.
 *  get min node in tree recursively 
 */
t_gen tree_get_min_rcrs(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	
	// tree is empty
	if (cur == NULL) {
		return NULL;
	} 

	// recursively traverse to left most node
	if (cur->lchild == NULL) {
		return cur->key;
	} else {
		return tree_get_min_rcrs(cur->lchild);
	}
}

/*! \brief Brief description.
 *  get max node in tree recursively 
 */
t_gen tree_get_max_rcrs(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	
	// tree is empty
	if (cur == NULL) {
		return NULL;
	} 

	// recursively traverse to right most node
	if (cur->rchild == NULL) {
		return cur->key;
	} else {
		return tree_get_max_rcrs(cur->rchild);
	}
}

/*! \brief Brief description.
 *  Destroy the instance of the tree 
 */
t_gen tree_node_predecessor(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
}

/*! \brief Brief description.
 *  Destroy the instance of the tree 
 */
t_gen tree_node_successor(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;

}

/*! \brief Brief description.
 *  Delete a node in the tree 
*/
t_gen tree_delete_node(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;

	return data;
}

/*! \brief Brief description.
 *  Destroy the instance of the tree 
 */
void destroy_tree(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	t_queue *q;

	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
	} else {
		q = create_queue("Qdel_tree", 40, eARRAY_QUEUE_CIRC, eUSER);
		// enqueue the root node
		q->enq(q, cur);

		// loop till queue is empty
		while (q->empty(q) != true) {
			// delete each node in the queue one by one after pushing their
			// non-empty left and right child to the queue
			cur =  q->deq(q);

			if (cur->lchild != NULL) {
				q->enq(q, cur->lchild);
			}

			if (cur->rchild != NULL) {
				q->enq(q, cur->rchild);
			}

			cur->lchild = cur->rchild = NULL;
			t->free(cur->key, __FILE__, __LINE__);
			free_mem(cur);
		}
		destroy_queue(q);
	}
	
	free_mem(t);
}

/*! \brief Brief description.
 *  print tree info
 */
void print_tree(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	t_queue *q;
	
	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
	} else {
		q = create_queue("Qtree_print", 40, eARRAY_QUEUE_CIRC, eUSER);
		
		printf("%s:", t->name);
		// enqueue the root node
		q->enq(q, cur);
		// loop till queue is empty
		while (q->empty(q) != true) {
			// delete each node in the queue one by one after pushing their
			// non-empty left and right child to the queue
			cur =  q->deq(q);

			if (cur->lchild != NULL) {
				q->enq(q, cur->lchild);
			}

			if (cur->rchild != NULL) {
				q->enq(q, cur->rchild);
			}

			t->print_data(cur->key);
			printf(" ");
		}
		printf("\n");
		destroy_queue(q);
	}
}
