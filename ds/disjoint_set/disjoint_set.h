/*! @file disjoint_set.h
    @brief 
    Contains declations of disjoint_set types, operations and structure
*/
#pragma once
#include "common.h"

/// Disjoint set node definition
typedef struct t_djset_node {
	int size;			///< size of the current set
	int parent;			///< Parent idx of the set
} t_dsetnode;

///Disjoint set operations func pointers
typedef int (*f_set1)(t_gen, int);	
typedef int (*f_set2)(t_gen, int, int);

/// Disjoint set main struct definition
typedef struct disjoint_set { 
	char *name; 			///< Name of link list instance */
	int size;			///< Max size of elems stored in disjoint set
	t_dsetnode *subset;		///< Pointer to N sets
	
	f_vgen make;			///< routine to add an new elem to the set
	f_set1 find;			///< routine to find an elem in the set
	f_set2 merge;			///< routine to merge to set
	
	f_print print;			///< routine to print elements in the disjoint set
	f_destroy destroy;		///< routine to destroy the instace of disjoint set
} t_disjset;

t_gen create_disjoint_set(char *name, int size);
