/*! @file heap.h
    @brief 
    Contains declations of heap types, operations and structure
*/
#pragma once 
#include "common.h"

/// Types of heaps
typedef enum {
	eMIN_HEAP,		///< Minimum Heap	
	eMAX_HEAP,		///< Maximum Heap
} e_heaptype;


/// Heap struct defn
typedef struct heap {
	// heap info params
	char *name;		///< Stack instance name
	int count;		///< Total elems present in heap
	int size;		///< Max Size of heap
	e_heaptype type;	///< Stack Type @see types of heap
	// data on which heap operates
	t_gen *data;		///< Ptr to array based heap 
	
	// heap  roputines
	f_ins insert;		///< routine to insert elements in heap 
	f_gen del;   		///< routine to delete elements in heap
	f_vgen build; 		///< routine to heapify
	f_vgen sort;  		///< routine to heap sort 
	f_len len;    		///< routine to get heap len
	f_print print;		///< routine to print heap info 
	f_destroy destroy;	///< routine to destroy

	// routies for operating on data
	f_cmp_idx cmpr_idx;
	f_cpy_idx copy_idx;
	f_swp_idx swap_idx;
	f_get_idx get_idx;
	f_print print_data;
} t_heap;

// Heap interface API
t_gen create_heap(char *name, t_gen data,int size, e_heaptype htype, t_dparams *prm);
