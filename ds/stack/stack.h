#pragma once 

#include "common.h"
#include "link_list.h"

#define MAX_STACK_SIZE	100

typedef int (*f_push)(t_data s, int data);
typedef int (*f_pop)(t_data s);

typedef enum {
	eLL_STACK,
	eARRAY_STACK,
	eARRAY_STACK_DOWN,
} e_stacktype;

typedef struct stack {
	char *name;
	t_linklist data;

	f_push push;
	f_pop pop;
	f_print print;
	f_full full;
	f_empty empty;
	f_size size;
}t_llstack;

typedef struct stack {
	int count;
	int max_size;
	int head;
	int *data;

	f_push push;
	f_pop pop;
	f_print print;
	f_full full;
	f_empty empty;
	f_size size;
}t_arrstack;

t_data create_stack (char *name, int max_size, e_stacktype type);
void destroy_stack (t_data s);
void print_stack(t_data s);
int push_stack(t_data s, int data);
int pop_stack(t_data s);
t_elem* peek_stack(t_data s,int idx);
void print_stack(t_data s);
int stack_size(t_data s);
bool is_stack_full(t_data s);
bool is_stack_empty(t_data s);
