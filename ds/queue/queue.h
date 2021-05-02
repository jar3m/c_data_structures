#pragma once

#include "common.h"
#include "link_list.h"

typedef t_gen (*f_enq)(t_gen s, t_gen data);
typedef t_gen (*f_deq)(t_gen s);

typedef enum {
	eLL_QUEUE_CIRC,
	eARRAY_QUEUE_CIRC,
} e_queuetype;

typedef struct {
	char *name;
	int max_size;
	int count;
	int front;
	int rear;
	e_queuetype type;
	t_gen *data;
	
	f_enq enq;
	f_deq deq;
	f_len len;
	f_free free;
	f_full full;
	f_empty empty;
	f_print print;
	f_print print_data;
} t_queue;


t_gen create_queue (char *name, int max_size, e_queuetype type, e_data_types dtype);
void destroy_queue (t_gen s);
void print_queue(t_gen s);
