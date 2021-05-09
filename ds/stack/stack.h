#pragma once 

#include "common.h"
#include "link_list.h"

#define MAX_STACK_SIZE	100

///func ptr defn for stack operations
typedef t_gen (*f_push)(t_gen s, t_gen data);
typedef t_gen (*f_pop)(t_gen s);

///types of supported stacks
typedef enum {
	eLL_STACK,
	eARRAY_STACK,
	eARRAY_STACK_DOWN,
} e_stacktype;

/// stack struct defn
typedef struct stack {
	/// stack count, size and top refr
	char *name;
	int count;
	int max_size;
	int top;
	e_stacktype type;
	/// link List or array based stack
	t_gen *data;
	/// stack operations
	f_push push;
	f_pop pop;
	f_gen peek;
	f_print print_data;
	f_full full;
	f_empty empty;
	f_len len;
	f_free free;
}t_stack;

t_gen create_stack (char *name, int max_size, e_stacktype stype,e_data_types dtype);
void destroy_stack (t_gen s);
void print_stack(t_gen s);
t_elem* peek_stack(t_gen s,int idx);
void print_stack(t_gen s);
