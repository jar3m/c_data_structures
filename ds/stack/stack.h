/*! @file stack.h
    @brief 
    Contains declations of stack types, operations and structure
*/
#pragma once 

#include "common.h"
#include "link_list.h"


/// func ptr defn for stack operations
typedef t_gen (*f_push)(t_gen s, t_gen data); 	///< Fn ptr for stack push operations
typedef t_gen (*f_pop)(t_gen s); 		///< Fn ptr for stack pop operations

/// types of supported stacks
typedef enum {
	eLL_STACK,				///< LinkList based Stack
	eARRAY_STACK,				///< Top Growing Stack
	eARRAY_STACK_DOWN,			///< Down Growing Stack
} e_stacktype;

/// stack struct defn
typedef struct stack {
	// stack count, size and top refr
	char *name;				///< Stack instance name
	int count;				///< Total elems present in stack
	int max_size;				///< Max Size of stack
	int top;				///< Stack Top
	e_stacktype type;			///< Stack Type @see types of stack
	// link List or array based stack
	t_gen *data;				///< Ptr to link List or array based on type of stack
	/// stack operations
	f_push push;				///< routine to push element into stack
	f_pop pop;				///< routine to pop element into stack
	f_gen peek;				///< routine to peek elements in stack
	f_full full;				///< routine to check if stack is full
	f_empty empty;				///< routine to check if stack is empty
	f_len len;				///< routine to get len of stack
	f_print print;				///< routine to print stack contents

	/// routies for operating on data
	f_free free;
	f_print print_data;
}t_stack;

// API
t_gen create_stack (char *name, int max_size, e_stacktype stype,e_data_types dtype);
void destroy_stack (t_gen s);
void stack_print(t_gen s);
