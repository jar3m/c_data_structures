#include "stack.h"

bool is_stack_full(t_gen d);
bool is_stack_empty(t_gen d);
int stack_size(t_gen d);

t_gen push_stack_arr_up(t_gen d, t_gen data);
t_gen pop_stack_arr_up(t_gen s);
t_gen push_stack_arr_down(t_gen d, t_gen data);
t_gen pop_stack_arr_down(t_gen d);
t_gen push_stack_ll_up(t_gen d, t_gen data);
t_gen pop_stack_ll_up(t_gen d);

f_push stack_push[] = {push_stack_ll_up, push_stack_arr_up, push_stack_arr_down};
f_pop stack_pop[] = {pop_stack_ll_up, pop_stack_arr_up, pop_stack_arr_down};

/*! \brief Brief description.
 *  Create an instance of stack
*/
t_gen create_stack (char *name, int max_size, e_stacktype stype, e_data_types dtype)
{
        t_stack *s = get_mem(1, sizeof(t_stack));
	
	// Init stack variables
        s->name = name;
        s->max_size = max_size;
        s->type = stype;
        s->count = 0;
	
	// Bind stack routines
	s->full = is_stack_full;
	s->empty = is_stack_empty;
	s->len = stack_size;
	s->free = FREE_MEM;

        // Initialize top of stack to max size if down growing
        s->top = (stype == eARRAY_STACK_DOWN) ? max_size : -1;

	// Bind stack routines and create stack space based on stack type
	s->push = stack_push[stype];	
	s->pop = stack_pop[stype];	

        switch (stype) 
	{
		case eLL_STACK:
			s->data = create_link_list("stack_data", eSINGLE_LINKLIST, dtype);
		break;
		case eARRAY_STACK:
		case eARRAY_STACK_DOWN:
			s->data = get_mem(max_size, sizeof(t_gen));
		break;
        }

        return (t_gen) s;
}

/*! \brief Brief description.
 *  Destroy stack instance 
*/
void destroy_stack (t_gen d)
{
        t_stack *s = (t_stack*)d;
	int i;

	// Free created stack space
        switch (s->type) 
	{
		case eLL_STACK:
			destroy_link_list(s->data);
		break;
		case eARRAY_STACK:
		case eARRAY_STACK_DOWN:
			while (s->empty(s) != true) {
				s->free(s->pop(s), __FILE__, __LINE__);
			}
			free_mem(s->data);
		break;
        }

	// Free stack
	free_mem(s);
}


/*! \brief Brief description.
 *  Check stack full 
*/
bool is_stack_full(t_gen d)
{
	return ((t_stack*)d)->count >= ((t_stack*)d)->max_size;
}

/*! \brief Brief description.
 *  Check stack empty 
*/
bool is_stack_empty(t_gen d)
{
	return ((t_stack*)d)->count == 0;
}

/*! \brief Brief description.
 *  Return stack size
*/
int stack_size(t_gen d)
{
	return ((t_stack*)d)->count;
}

/*! \brief Brief description.
 *  Push an element into up growing stack
*/
t_gen push_stack_arr_up(t_gen d, t_gen data)
{
	t_stack *s = (t_stack*)d; 
	
	// Return id stack full
	if (s->count >= s->max_size) {
		LOG_WARN("STACKS", "%s: Stack Full\n",s->name);
		return NULL;
	}
	// Incr top and push to stack
	s->data[++(s->top)] =  data;
	s->count++;

	return data;
}

/*! \brief Brief description.
 *  Pop an element from up growing stack
*/
t_gen pop_stack_arr_up(t_gen d)
{
	t_stack *s = (t_stack*)d; 
	t_gen data = NULL;

	if (s->count == 0) {
		LOG_WARN("STACKS", "%s: Stack empty\n",s->name);
		return data;
	}
	
	// Incr top and push to stack
	data = s->data[(s->top)--];
	s->count--;

	return data;
} 

/*! \brief Brief description.
 *  Push an element into down growing stack
*/
t_gen push_stack_arr_down(t_gen d, t_gen data)
{
	t_stack *s = (t_stack*)d; 
	
	// Return id stack full
	if (s->count >= s->max_size) {
		LOG_WARN("STACKS", "%s: Stack Full\n",s->name);
		return NULL;
	}
	// Incr top and push to stack
	s->data[--(s->top)] =  data;
	s->count++;

	return data;
}

/*! \brief Brief description.
 *  Pop an element from down growing ll stack
*/
t_gen pop_stack_arr_down(t_gen d)
{
	t_stack *s = (t_stack*)d; 
	t_gen data = NULL;

	if (s->count == 0) {
		LOG_WARN("STACKS", "%s: Stack empty\n",s->name);
		return data;
	}
	
	// Incr top and push to stack
	data = s->data[s->top++];
	s->count--;

	return data;
}

/*! \brief Brief description.
 *  Push an element into up growing ll stack
*/
t_gen push_stack_ll_up(t_gen d, t_gen data)
{	
	return NULL;
}

/*! \brief Brief description.
 *  Pop an element from up growing ll stack
*/
t_gen pop_stack_ll_up(t_gen d)
{	
	return NULL;
}

/*! \brief Brief description.
 *  print_stack_info
*/
void print_stack(t_gen d)
{
	t_stack *s = (t_stack*)d; 
	int i;

	printf("%s {max: %d} {size: %d} {top: %d} \n[",s->name,
			s->max_size, s->count,s->top);
	for (i = 0; i < s->count; i ++) {
		//printf("%d ",*(int*)(s->data[i]));
	}
	printf("]\n");
}
