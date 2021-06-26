/*! @file queue.h
    @brief 
    Contains declations of queue types, operations and structure
*/
#pragma once

#include "common.h"
#include "link_list.h"

/// func ptr defn for queue operations
typedef t_gen (*f_deq)(t_gen s);

/// types of queue
typedef enum {
	eLL_QUEUE_CIRC,		///< Link List Based Queue
	eARRAY_QUEUE_CIRC,	///< Array Based Queue
} e_queuetype;

/// queue struct defn
typedef struct {
	// queue prams
	char *name;		///< Stack instance name
	int max_size;		///< Max Size of queue
	int count;		///< Total elems present in queue
	int front;		///< Queue Front Pointer
	int rear;		///< Queue Rear Pointer
	e_queuetype type;	///< Stack Type @see types of queue

	// link List or array based queue
	t_gen *data;		///< Ptr to link List or array based on type of queue
	
	f_ins enq;		///< routine to push elements to queue
	f_deq deq;		///< routine to pop elements out of queue
	f_len len;	  	///< routine to get length queue 
	f_gen peek;	   	///< routine to peek node in queue
	f_full full;	   	///< routine to check if queue full
	f_empty empty;	   	///< routine to check if queue empty
	f_print print;	   	///< routine to print queue elements

	///< routines for operating on data
	f_print print_data;	
	f_free free;		
} t_queue;

// API
t_gen create_queue (char *name, int max_size, e_queuetype type, e_data_types dtype);
void destroy_queue (t_gen s);
void print_queue(t_gen s);
