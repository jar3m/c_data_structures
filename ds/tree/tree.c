/*! @file tree.c
    @brief 
    Contains definitions of routines supported by tree 
*/
#include "tree.h"
#include "stack.h"
#include "queue.h"

void tree_insert_node_bst(t_gen,t_gen);
t_gen tree_delete_node_bst(t_gen,t_gen);
int tree_height_bst (t_gen n);

t_gen tree_find_node(t_gen,t_gen);
t_gen tree_node_predecessor(t_gen,t_gen);
t_gen tree_node_successor(t_gen,t_gen);
t_gen tree_get_min(t_gen);
t_gen tree_get_max(t_gen);
void tree_inorder(t_gen);
void tree_preorder(t_gen);
void tree_postorder(t_gen);
void print_tree(t_gen);
int tree_node_count(t_gen n);

void tree_insert_node_avl(t_gen,t_gen);
t_gen tree_delete_node_avl(t_gen,t_gen);
int tree_height_avl(t_gen n);
void destroy_tree(t_gen);

/// Look Up function ptrs for inserting elem to tree
f_ins tree_insert[] = {tree_insert_node_bst,tree_insert_node_avl};

/// Look Up function ptrs for deleting elem to tree
f_del tree_del[] = {tree_delete_node_bst,tree_delete_node_avl};

/// Look Up function ptrs for getting height of tree
f_len tree_height[] = {tree_height_bst, tree_height_avl};

/*! @brief  
 *  Create an instance of tree
 *  @param name	 - Name of tree instance
 *  @param ttype - Type of tree to be created
 *  @param prm   - Data type specific parameters
 *  @return 	 - Pointer to instance of tree
 * */
t_gen create_tree(char *name, e_treetype ttype, t_dparams *prm)
{
	t_tree *t = get_mem(1, sizeof(t_tree));

	// Initailze tree Params
	t->name       = name;
	t->type       = ttype;
	t->count      = 0;
	t->root       = NULL;
	
	// Initailze tree routines
	t->insert     = tree_insert[ttype]; 
	t->del        = tree_del[ttype];
	t->find       = tree_find_node;
	t->pred       = tree_node_predecessor;
	t->succ       = tree_node_successor;
	t->min        = tree_get_min;
	t->max        = tree_get_max;
	t->print      = print_tree;
	t->inorder    = tree_inorder;
	t->preorder   = tree_preorder;
	t->postorder  = tree_postorder;
	t->height     = tree_height[ttype];
	t->node_count = tree_node_count;
	t->destroy    = destroy_tree;

	// Initailze datatype based operations req for prop working of tree
	t->cmpr       = prm->cmpr;
	t->swap       = prm->swap;
	t->print_data = prm->print_data;
	t->free       = prm->free;

	return (t_gen)t;
}                  
                   

/*! @brief  
 *   get_num_nodes in tree;
 *  @param d	- Pointer instance of tree
 *  @return 	- count of nodes
 */
int tree_node_count(t_gen d)
{

	return ((t_tree*)d)->count;
}

/*! @brief  
 *   Add element to a bst tree
 *  @param d	- Pointer instance of tree
 *  @param data - Pointer data
 *  @return 	- NA
 */
void tree_insert_node_bst(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *new;
	t_tree_node *parent = NULL, *cur;
	e_cmpr res;

	// key already present
	if (t->find(t, data) != NULL) {
		LOG_WARN("TREES", "%s: Key not present\n");
		return;
	} 

	t->count++;
	// Create Node and add data
	new = get_mem(1, sizeof(t_tree_node));
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

/*! @brief  
 *   find an element in tree
 *  @param d	- Pointer instance of tree
 *  @param data - Pointer data
 *  @return 	- NULL if data absent else node pointer
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

/*! @brief  
 *  get min node in tree 
 *  @param root - Pointer to root
 *  @return 	- min node
 */
t_gen tree_get_min(t_gen root)
{
	t_tree_node *cur = (t_tree_node*)root;
	
	// tree is empty
	if (cur == NULL) {
		return NULL;
	}

	// left most node contains min
	while (cur->lchild != NULL) {
		cur = cur->lchild;
	}

	return cur;
}

/*! @brief  
 *  get max node in tree 
 *  @param root - Pointer to root
 *  @return 	- max node
 */
t_gen tree_get_max(t_gen root)
{
	t_tree_node *cur = (t_tree_node*)root;
	
	// tree is empty
	if (cur == NULL) {
		return NULL;
	}

	// right most node contains min
	while (cur->rchild != NULL) {
		cur = cur->rchild;
	}

	return cur;
}

/*! @brief  
 *  get min node in tree recursively 
 *  @param root - Pointer to root
 *  @return 	- min node
 */
t_gen tree_get_min_rcrs(t_gen root)
{
	t_tree_node *cur = (t_tree_node*)root;
	
	// tree is empty
	if (cur == NULL) {
		return NULL;
	} 

	// recursively traverse to left most node
	if (cur->lchild == NULL) {
		return cur;
	} else {
		return tree_get_min_rcrs(cur->lchild);
	}
}

/*! @brief  
 *  get max node in tree recursively 
 *  @param root - Pointer to root
 *  @return 	- max node
 */
t_gen tree_get_max_rcrs(t_gen root)
{
	t_tree_node *cur = (t_tree_node*)root;
	
	// tree is empty
	if (cur == NULL) {
		return NULL;
	} 

	// recursively traverse to right most node
	if (cur->rchild == NULL) {
		return cur;
	} else {
		return tree_get_max_rcrs(cur->rchild);
	}
}

/*! @brief  
 *  find the predecessor of a given node in tree 
 *  @param d    - Pointer to instance of tree
 *  @param data - Pointer to data
 *  @return 	- predcessor node pointer
 */
t_gen tree_node_predecessor(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *pred = NULL, *cur = t->root;
	e_cmpr res;

	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return pred;
	} 
	
	while (cur) {
		res = t->cmpr(data, cur->key);
		
		// if key is less than cur, visit the left subtree
		if (res == eLESS) {
			cur = cur->lchild;
		}
		// if key is less than cur, visit the right subtree
		else if (res == eGREAT) {
			// set the pred as cur before visiting right subtree
			pred = cur;
			cur = cur->rchild;
		}
		// Node found and pred is max of left subtree (if any)
		// else pred is root of last right subtreee traversal
		else {
			if (cur->lchild != NULL) {
				pred = t->max(cur->lchild);
			}
			break;
		}
	}

	// key not present
	if (cur == NULL || pred == NULL) {
		LOG_WARN("TREES", "%s: Key not present\n",t->name);
		pred = NULL;
	} 

	return pred;
}

/*! @brief  
 *  find the successor of a given node in tree 
 *  @param d    - Pointer to instance of tree
 *  @param data - Pointer to data
 *  @return 	- successor node pointer
 */
t_gen tree_node_successor(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *succ = NULL, *cur = t->root;
	e_cmpr res;

	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return succ;
	} 
	
	while (cur) {
		res = t->cmpr(data, cur->key);
		
		// if key is less than cur, visit the left subtree
		// set the succ as cur before visiting left subtree
		if (res == eLESS) {
			succ = cur;
			cur = cur->lchild;
		}
		// if key is less than cur, visit the right subtree
		else if (res == eGREAT) {
			cur = cur->rchild;
		}
		// Node found and succ is min of right subtree (if any)
		// else succ is root of last left subtreee traversal
		else {
			if (cur->rchild != NULL) {
				succ = t->min(cur->rchild);
			}
			break;
		}
	}

	// key not present
	if (cur == NULL || succ == NULL) {
		LOG_WARN("TREES", "%s: Key not present\n",t->name);
		succ = NULL;
	} 
	
	return succ;
}

/*! @brief  
 *  Delete a node in a bst tree 
 *  @param d    - Pointer to instance of tree
 *  @param data - Pointer to data of node to delete
 *  @return 	- NULL of data not present else data pointer
*/
t_gen tree_delete_node_bst(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *tmp, *prv, *cur = t->root;
	e_cmpr res;
	t_gen ret = NULL;
	
	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return ret;
	} 

	t->count++;
	tmp = prv = NULL;
	// check if node present and get parent
	while (cur) {
		res = t->cmpr(data, cur->key);
		if (res == eEQUAL) {
			break;
		}
		
		prv = cur;
		if (res == eLESS) {
			cur = cur->lchild;
		} else {
			cur = cur->rchild;
		}
	}

	// key not present
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: Key not present\n",t->name);
		return ret;
	} 

	// store the key to be returned	
	ret = cur->key;

	// node to be  has just one child
	if (cur->lchild == NULL || cur->rchild == NULL) {
		// get the non-null child to be replaced with deleted node
		tmp =  (cur->lchild != NULL)? cur->lchild : cur->rchild;
		
		// root is deleted update root
		if (prv == NULL) {
			t->root = tmp;
		}
		//  get where the new node is to updated ,i.e. l or r child
		else if (cur == prv->lchild) {
			prv->lchild = tmp;
		}
		 else {
			prv->rchild = tmp;
		}
	}
	 
	else {
		prv = NULL;
		// compute successor and get parent of it
		tmp = cur->rchild;
		while (tmp->lchild) {
			prv = tmp;
			tmp = tmp->lchild;
		}

		// Swap node to be deleted with succ 
		if (prv != NULL) {
			prv->lchild = tmp->rchild;
		} 
		else {
			cur->rchild = tmp->rchild;
		}
		
		cur->key = tmp->key;
		cur = tmp;
	}
	// Delete node
	cur->lchild = cur->rchild = NULL;
	cur->key = NULL;
	free_mem(cur);

	return ret;
}

/*! @brief  
 *   get height of bst
 *  @param d    - Pointer to node
 *  @return 	- height of tree from given node
 */
int tree_height_bst (t_gen n)
{
	t_tree_node *cur = (t_tree_node*)n;
	int height = 0,size;
	t_queue *q;
	t_dparams dp;
	
	if (cur == NULL) {
		return height;
	}

	// TODO: Queue count how to do??
	init_data_params(&dp, eINT32);
	q = create_queue("Qdel_tree", 40, eLL_QUEUE_CIRC, &dp);

	// enqueue the root node
	q->enq(q, cur);
	while (q->empty(q) != true) {
		// nodes in current level
		size = q->len(q);
		// loop till queue is empty
		while (size--) {
			// get the node at cur level
			cur =  q->deq(q);

			// enqueue all the children at cur lvl
			if (cur->lchild != NULL) {
				q->enq(q, cur->lchild);
			}

			if (cur->rchild != NULL) {
				q->enq(q, cur->rchild);
			}
		}
		
		// Increment height
		height++;
	}
	
	q->destroy(q);

	return height;

}

/*! @brief  
 *  Destroy the instance of the tree 
 *  @param d    - Pointer to instance of tree
 *  @return 	- NA
 */
void destroy_tree(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	t_queue *q;
	t_dparams dp;

	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
	} else {
		init_data_params(&dp, eINT32);
		q = create_queue("Qdel_tree", t->count,
				eLL_QUEUE_CIRC, &dp);
		// enqueue the root node
		q->enq(q, cur);

		// loop till queue is empty
		while (q->empty(q) != true) {
			// delete nodes in the queue one by one after pushing 
			// their non-empty left and right child to the queue
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
		q->destroy(q);
	}
	
	free_mem(t);
}

/*! @brief  
 *  postorder traverse tree
 *  @param d    - Pointer to instance of tree
 *  @return 	- NA
 */
void  tree_postorder(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *tmp, *cur = t->root;
	t_dparams dp;
	t_stack *s;
	 
	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return;
	}
	printf("%s: %d nodes postorder traversal\n", t->name, t->count);
	
	init_data_params(&dp, eINT32);
	s = create_stack("Stk_postorder", t->count, eLL_STACK, &dp);

	do {
		// Move to left most node
		while (cur) {
			// push root rchild and root to stack
			if (cur->rchild != NULL) {	
				s->push(s, cur->rchild);
			}			
			s->push(s, cur);
			cur = cur->lchild;
		}
		// pop and print the node
		cur = s->pop(s);
	
		//  If popped item has right child and the right child is not
		// processed, then make sure right child processed before root
		tmp = (s->empty(s) != true)? s->peek(s, 0): NULL;
		
		if (cur->rchild != NULL && tmp == cur->rchild) {
			// remove right child from stack
			s->pop(s);
			// push root back to stack
			s->push(s, cur);
			// update root to rchild to process it
			cur = cur->rchild;
		}
		else {
			// print data and update root as NULL
			t->print_data(cur->key);
			printf(" ");
			cur = NULL;
		}
	} while (s->empty(s) != true);
	printf("\n");
	
	s->destroy(s);

}

/*! @brief  
 *  preorder traverse tree
 *  @param d    - Pointer to instance of tree
 *  @return 	- NA
 */
void  tree_preorder(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	t_stack *s;
	t_dparams dp;
	 
	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return;
	}
	printf("%s: %d nodes preorder traversal\n", t->name, t->count);

	init_data_params(&dp, eINT32);
	s = create_stack("Stk_inorder", t->count, eLL_STACK, &dp);

	// push root node
	s->push(s, cur);
	while (s->empty(s) != true) {
		// pop and print the node
		cur = s->pop(s);
		t->print_data(cur->key);
		printf(" ");

		// push right and left child of node
		if (cur->lchild != NULL) {
			s->push(s, cur->lchild);
		}
		if (cur->rchild != NULL) {
			s->push(s, cur->rchild);
		}
	}
	printf("\n");
	
	s->destroy(s);
}

/*! @brief  
 *  inorder traverse tree
 *  @param d    - Pointer to instance of tree
 *  @return 	- NA
 */
void  tree_inorder(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	t_stack *s;
	t_dparams dp;
	 
	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return;
	}
	printf("%s: %d nodes inorder traversal\n", t->name, t->count);

	init_data_params(&dp, eINT32);
	s = create_stack("Stk_inorder", t->count, eLL_STACK, &dp);

	while (s->empty(s) != true || cur != NULL) {
		// Visit the left most child
		while (cur != NULL) {
			s->push(s, cur);
			cur = cur->lchild;
		} 
	
		// pop and print the node
		cur = s->pop(s);
		t->print_data(cur->key);
		printf(" ");

		// traverse the right subtree
		cur = cur->rchild;
	}
	printf("\n");
	
	s->destroy(s);
}

/*! @brief  
 *  print tree info level by level
 *  @param d    - Pointer to instance of tree
 *  @return 	- NA
 */
void print_tree(t_gen d)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *cur = t->root;
	t_queue *q;
	t_dparams dp;
	int level = 0,size;

	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return;
	}
	printf("%s: %d nodes lvl based print \n", t->name,t->count);

	init_data_params(&dp, eINT32);
	q = create_queue("Qdel_tree", t->count, eLL_QUEUE_CIRC, &dp);

	// enqueue the root node
	q->enq(q, cur);
	while (q->empty(q) != true) {
		printf(" %d :",level);
		// nodes in current level
		size = q->len(q);
		// loop till queue is empty
		while (size--) {
			// get the node at cur level
			cur =  q->deq(q);

			printf("[");
			t->print_data(cur->key);
			printf(":");
			// enqueue all the children at cur lvl
			if (cur->lchild != NULL) {
				q->enq(q, cur->lchild);
				printf(" ");
				t->print_data(cur->lchild->key);
			}

			if (cur->rchild != NULL) {
				q->enq(q, cur->rchild);
				printf(" ");
				t->print_data(cur->rchild->key);
			}
			// print all nodes at cur lvl
			printf("] ");
		}
		printf("\n");
		// Increment level
		level++;
	}
	
	q->destroy(q);

}

/*! @brief  
 *   get height of avl subtree 
 *  @param n    - Pointer to node
 *  @return 	- height of given subtree
 */
int tree_height_avl (t_gen n)
{
	t_tree_node *root = (t_tree_node*)n;
	int lh, rh;
	int height;
	
	lh = (root->lchild == NULL)? -1: root->lchild->height; 
	rh = (root->rchild == NULL)? -1: root->rchild->height; 
	
	height = (lh >rh)? lh: rh;

	return 1 + height;

}

/*! @brief  
 *   get slope of node subtree
 *  @param n    - Pointer to node
 *  @return 	- slope of given subtree
 */
int tree_slope(t_gen n)
{
	t_tree_node *root = (t_tree_node*)n;
	int lh, rh;

	lh = (root->lchild == NULL)? 0: root->lchild->height; 
	rh = (root->rchild == NULL)? 0: root->rchild->height; 

	return (lh - rh); 
}

/*! @brief  
 *   rotate subtree right
 *  @param n    - Pointer to node
 *  @return 	- NA
 */
void tree_rotate_right(t_gen n)
{
	t_tree_node *root = (t_tree_node*)n;
	t_tree_node *TLL, *TLR, *TR;
	t_gen x, y;

	// update all ptrs;
	x = root->key;
	y = root->lchild->key;
	TLL = root->lchild->lchild;
	TLR = root->lchild->rchild;
	TR = root->rchild;

	// rotate right
	root->key = y;
	root->rchild = root->lchild;
	root->rchild->key = x;
	root->lchild = TLL;
	root->rchild->lchild = TLR;
	root->rchild->rchild = TR;
}


/*! @brief  
 *   rotate subtree left
 *  @param n    - Pointer to node
 *  @return 	- NA
 */
void tree_rotate_left(t_gen n)
{
	t_tree_node *root = (t_tree_node*)n;
	t_tree_node *TLL, *TLRL, *TLRR;
	t_gen y, z;

	// update all ptrs;
	y = root->key;
	z = root->rchild->key;
	TLL = root->lchild;
	TLRL = root->rchild->lchild;
	TLRR = root->rchild->rchild;

	// rotate left
	root->key = z;
	root->lchild = root->rchild;
	root->lchild->key = y;
	root->lchild->lchild = TLL;
	root->lchild->rchild = TLRL;
	root->rchild = TLRR;
}

/*! @brief  
 *   rebalance subtree
 *  @param n    - Pointer to node
 *  @return 	- NA
 */
void tree_rebalance(t_gen n)
{
	t_tree_node *root = (t_tree_node*)n;

	if (tree_slope(root) == 2) {
		if (tree_slope(root->lchild) == -1) {
			tree_rotate_left(root->lchild);
		}
		tree_rotate_right(root);
	}
		
	if (tree_slope(root) == -2) {
		if (tree_slope(root->rchild) == 1) {
			tree_rotate_right(root->rchild);
		}
		tree_rotate_left(root);
	}
		
}

/*! @brief  
 *   Add element to an avl tree
 *  @param d    - Pointer to instance of tree
 *  @param data - Pointer to the data to be inserted
 *  @return 	- NA
 */
void tree_insert_node_avl(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *new;
	t_tree_node *parent = NULL, *cur;
	e_cmpr res;
	t_stack *s;
	t_dparams dp;

	// key already present
	if (t->find(t, data) != NULL) {
		LOG_WARN("TREES", "%s: Key not present\n");
		return;
	} 

	t->count++;
	// Create Node and add data
	new = get_mem(1, sizeof(t_tree_node));
	new->key = data;
	new->lchild = new->rchild = NULL;
	new->height = 0;

	// tree is empty
	if (t->root == NULL) {
		t->root = new;
		return;
	}

	// stack to be used to find rebalance and update height
	init_data_params(&dp, eINT32);
	s = create_stack("Stk_inorder", t->count, eLL_STACK, &dp);

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

		// push parent to stack 
		s->push(s, parent);
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

	// check for rebalance and update height
	while (s->empty(s) != true) {
		cur  = s->pop(s);
		// rebalance the paraent
		tree_rebalance(cur);
		cur->height = tree_height_avl(cur);	
	}

	s->destroy(s);
}


/*! @brief  
 *  Delete a node in an avl tree 
 *  @param d    - Pointer to instance of tree
 *  @param data - Pointer to the data to be deleted
 *  @return 	- Null if data not present else data pointer
*/
t_gen tree_delete_node_avl(t_gen d,t_gen data)
{
	t_tree *t = (t_tree*)d;
	t_tree_node *tmp, *prv, *cur = t->root;
	t_gen ret = NULL;
	e_cmpr res;
	t_dparams dp;
	t_stack *s;
	
	// Empty tree
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: TREE Empty\n",t->name);
		return ret;
	} 

	// stack to be used to find rebalance and update height
	init_data_params(&dp, eINT32);
	s = create_stack("Stk_inorder", t->count, eLL_STACK, &dp);

	t->count++;
	tmp = prv = NULL;
	// check if node present and get parent
	while (cur) {
		res = t->cmpr(data, cur->key);
		if (res == eEQUAL) {
			break;
		}
		
		prv = cur;
		if (res == eLESS) {
			cur = cur->lchild;
		} else {
			cur = cur->rchild;
		}
		// push parent to stack 
		s->push(s, prv);
	}

	// key not present
	if (cur == NULL) {
		LOG_WARN("TREES", "%s: Key not present\n",t->name);
		s->destroy(s);
		return ret;
	} 

	// store the key to be returned	
	ret = cur->key;

	// node to be  has just one child
	if (cur->lchild == NULL || cur->rchild == NULL) {
		// get the non-null child to be replaced with deleted node
		tmp =  (cur->lchild != NULL)? cur->lchild : cur->rchild;
		
		// root is deleted update root
		if (prv == NULL) {
			t->root = tmp;
		}
		//  get where the new node is to updated ,i.e. l or r child
		else if (cur == prv->lchild) {
			prv->lchild = tmp;
		}
		 else {
			prv->rchild = tmp;
		}
	}
	 
	else {
		prv = NULL;
		// compute successor and get parent of it
		tmp = cur->rchild;
		while (tmp->lchild) {
			prv = tmp;
			tmp = tmp->lchild;
		}

		// Swap node to be deleted with succ 
		if (prv != NULL) {
			prv->lchild = tmp->rchild;
		} 
		else {
			cur->rchild = tmp->rchild;
		}
		
		cur->key = tmp->key;
		cur = tmp;
	}
	// Delete node
	cur->lchild = cur->rchild = NULL;
	cur->key = NULL;
	free_mem(cur);

	// check for rebalance and update height
	while (s->empty(s) != true) {
		cur  = s->pop(s);
		// rebalance the paraent
		tree_rebalance(cur);
		cur->height = tree_height_avl(cur);	
	}

	s->destroy(s);
	return ret;
}
