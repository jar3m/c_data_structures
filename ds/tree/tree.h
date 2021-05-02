#pragma once
#include "common.h"

/// tree node 
typedef struct tree_node {
	t_gen key;
	struct tree_node *lchild;
	struct tree_node *rchild;
} t_tree_node;

/// Types of trees
typedef enum {
	eBST,
	eAVL,
} e_treetype;

// tree specific routines
typedef t_gen(*f_pred)(t_gen, t_gen);
typedef t_gen(*f_succ)(t_gen, t_gen);
typedef t_gen(*f_min_max)(t_gen);


/// Heap struct defn
typedef struct tree {
	// tree info params
	char *name;
	e_treetype type;
	int count;
	
	//tree root
	t_gen root;
	
	f_ins insert;
	f_del del;
	f_find find;
	f_pred predcessor;
	f_succ successor;
	f_min_max min;
	f_min_max max;
	f_print print;
	
	f_cmpr cmpr;
	f_swap swap;
	f_free free;
	f_print print_data;
} t_tree;

/// tree interface API
t_gen create_tree(char *name, e_treetype, e_data_types);
void destroy_tree(t_gen);
void print_tree(t_gen);
