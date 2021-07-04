/*! @file tree.h
    @brief 
    Contains declations of tree types, operations and structure
*/
#pragma once
#include "common.h"

/// tree node 
typedef struct tree_node {
	t_gen key;			///< Pointer to node key
	struct tree_node *lchild;	///< Pointer to node left child
	struct tree_node *rchild;	///< Pointer to node right child
	int height;			///< height of node
} t_tree_node;

/// Types of trees
typedef enum {
	eBST,				///< Binary Search Tree
	eAVL,				///< AVL Tree
} e_treetype;


/// tree struct defn
typedef struct tree {
	// tree info params
	char *name;			///< Tree instance name
	e_treetype type;		///< Tree Type @see types of trees
	int count;			///< Tree node count
	
	// tree root
	t_gen root;			///< Root node of the tree
	
	// tree routines
	f_ins insert;			///< routine to insert element in tree
	f_del del;   			///< routine to delete element in tree
	f_find find; 			///< routine to find element in tree
	f_gen2 pred; 			///< routine to get predecessor to given node
	f_gen2 succ; 			///< routine to get successor to given node
	f_gen min;   			///< routine to get minm element in tree
	f_gen max;   			///< routine to get maxm element in tree
	f_len height;			///< routine to get height of tree
	f_len node_count;		///< routine to get total nodes in tree
	f_print inorder; 		///< routine to print inorder traversal of tree 
	f_print preorder; 		///< routine to print preorder traversal of tree
	f_print postorder;		///< routine to print postorder traversal of tree
	f_print print;			///< routine to print tree level by level
	f_destroy destroy;		///< routine to destroy the tree instance
	
	// routies for operating on data
	f_cmpr cmpr;
	f_swap swap;
	f_free free;
	f_print print_data;
} t_tree;

/// tree interface API
t_gen create_tree(char *name, e_treetype, t_dparams *prm);
