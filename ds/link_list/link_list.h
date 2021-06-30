/*! @file link_list.h
    @brief 
    Contains declations of link list types, node and link list structure
*/
#pragma once

#include "common.h"

typedef t_gen(*f_del)(t_gen, t_gen);

/// Type of linklists
typedef enum {
	eSINGLE_LINKLIST,		///< Singly Link list	
	eDOUBLE_LINKLIST,		///< Doubly Link list
	eSINGLE_CIRCULAR_LINKLIST,	///< Singly Circular Link list
	eDOUBLE_CIRCULAR_LINKLIST,	///< Doubly Circular Link list
	eXOR_LINKLIST,			///< Xor Link list
}e_lltype;

/// Link list node definition
typedef struct llnode {
	t_gen data;			///< Pointer to the data to be stored in link list
	struct llnode *nxt;		///< Pointer to next node in list
	struct llnode *prv;		///< Pointer to prev node in list
} t_llnode;

/// Link List main structure
typedef struct linklist {
	char *name; 			///< Name of link list instance */
	e_lltype type;			///< Type of link list
	int count;			///< Total no of elems stored in link list
	e_data_types dtype;		///< Type of data elemnts to be stored

	// linklist head and tail ref
	t_llnode *head;			///< Head node reference
	t_llnode *tail;			///< Tail node reference
	
	// linklist routines
	f_ins append;			///< routine to Add elem at end of link list
	f_ins add;			///< routine to Add elem at begin of link list
	f_del del;			///< routine to del node with matching elem of link list
	f_find find;			///< routine to find and get the node with matching elem
	f_del_idx del_idx;		///< routine to del node at idx
	f_get_idx get_idx;		///< routine to get node at idx
	f_len len;			///< routine to get len of link list
	f_print print;			///< routine to print the link list 
	f_print print_info;		///< routine to print the detailed of link list
	f_gen head_node;		///< routine to get the head node
	f_gen tail_node;		///< routine to get the tail node
	f_gen end_node; 		///< routine to get the end node
	f_gen2 next_node;		///< routine to get the next node of the given node
	f_gen2 prev_node;		///< routine to get the prev node of the given node
	f_gen get_node_data;		///< routine to get data in given node
	f_destroy destroy;		///< routine destroy the link list instance

	/// routies for operating on data
	f_print print_data;		
	f_cmpr cmpr;			
	f_assign assign;		
	f_swap swap;			
	f_free free;			
} t_linklist;


//API
t_gen create_link_list (char *name, e_lltype type, t_dparams *dprm);
void destroy_link_list (t_gen d);
void linklist_print (t_gen d);
