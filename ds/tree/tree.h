#pragma once
#include "common.h"

/// tree node 
typedef struct tree_node {
	t_gen key;
	struct tree_node *lchild;
	struct tree_node *rchild;
	int height;
} t_tree_node;

/// Types of trees
typedef enum {
	eBST,
	eAVL,
} e_treetype;

// tree specific routines
typedef t_gen(*f_pred)(t_gen, t_gen);
typedef t_gen(*f_succ)(t_gen, t_gen);


/// Heap struct defn
typedef struct tree {
	// tree info params
	char *name;
	e_treetype type;
	int count;
	
	//tree root
	t_gen root;
	
	// tree roputines
	f_ins insert;
	f_del del;
	f_find find;
	f_pred pred;
	f_succ succ;
	f_gen min;
	f_gen max;
	f_len height;
	f_len node_count;
	f_print inorder;
	f_print preorder;
	f_print postorder;
	f_print print;
	
	// routies for operating on data
	f_cmpr cmpr;
	f_swap swap;
	f_free free;
	f_print print_data;
} t_tree;

/// tree interface API
t_gen create_tree(char *name, e_treetype, e_data_types);
void destroy_tree(t_gen);
void print_tree(t_gen);
