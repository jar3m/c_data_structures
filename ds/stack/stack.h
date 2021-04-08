#pragma once 

#include "common.h"
#include "link_list.h"

#define MAX_STACK_SIZE	100

typedef int (*f_push)(t_data s, int data);
typedef int (*f_pop)(t_data s);


typedef enum {
	eLL_STACK,
	eLL_STACK_DOWN;
	eARRAY_STACK,
	eARRAY_STACK_DOWN,
} e_stacktype;

typedef struct stack {
	t_linklist data;

	f_push push;
	f_pop pop;
	f_print print;
}t_llstack;

typedef struct stack {
	int count;
	int max_size;
	int head;
	int *data;

	f_push push;
	f_pop pop;
	f_print print;
}t_arrstack;

t_data create_stack (char *name, int max_size, e_stacktype type);
void destroy_stack (t_data s);
void print_stack(t_data s);
int push_stack(t_data s, int data);
int pop_stack(t_data s);
t_elem* peek_stack(t_data s,int idx);
void print_stack(t_data s);
