#include "stack.h"

bool is_stack_full(t_gen d);
bool is_stack_empty(t_gen d);
int stack_size(t_gen d);

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

        // Initialize top of stack to max size if down growing
        s->top = (stype == eARRAY_STACK_DOWN) ? max_size : 0;

	// Bind stack routines and create stack space based on stack type
        switch (stype) 
	{
		case eLL_STACK:
			s->data = create_link_list("stack_data", eSINGLE_LINKLIST, dtype);
		break;
		case eARRAY_STACK:
		case eARRAY_STACK_DOWN:
			s->data = get_mem(1, sizeof(t_gen) * max_size);
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
	
	// Free created stack space
        switch (s->type) 
	{
		case eLL_STACK:
			destroy_link_list(s->data);
		break;
		case eARRAY_STACK:
		case eARRAY_STACK_DOWN:
			free_mem(s->data);
		break;
        }

	// Clear stack variables and fn ptrs
	s->count = s->max_size = s->top = 0;
	// Free stack
	free_mem(s);
}

/*! \brief Brief description.
 *  Check stack full 
*/
bool is_stack_full(t_gen d)
{
	return ((t_stack*)d)->count == ((t_stack*)d)->max_size;
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


