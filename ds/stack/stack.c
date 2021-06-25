/*! @file stack.c
    @brief 
    Contains definitions of routines supported by stack 
*/

#include "stack.h"

bool is_stack_full(t_gen d);
bool is_stack_empty(t_gen d);
int stack_size(t_gen d);
t_gen stack_peek(t_gen d);

t_gen push_stack_arr_up(t_gen d, t_gen data);
t_gen pop_stack_arr_up(t_gen s);
t_gen push_stack_arr_down(t_gen d, t_gen data);
t_gen pop_stack_arr_down(t_gen d);
t_gen push_stack_ll(t_gen d, t_gen data);
t_gen pop_stack_ll(t_gen d);

char * get_name(e_stacktype type); 

/// Look Up function ptrs for pushing to stack
f_push stack_push[] = {push_stack_ll, push_stack_arr_up, push_stack_arr_down};

/// Look Up function ptrs for poping to stack
f_pop stack_pop[] = {pop_stack_ll, pop_stack_arr_up, pop_stack_arr_down};

/*! @brief  
 *  Create an instance of stack
 *  @param name     - Name of stack instance
 *  @param max_size - Max size of stack instance
 *  @param type     - Type of stack to be created
 *  @param prm      - Data type specific parameters
 *  @return         - Pointer to instance of stack
*/
t_gen create_stack (char *name, int max_size, e_stacktype stype, e_data_types dtype)
{
        t_stack *s = get_mem(1, sizeof(t_stack));
	
	// Init stack variables
        s->name 	= name;
        s->max_size 	= max_size;
        s->type 	= stype;
        s->count 	= 0;
	
        // Initialize top of stack to max size if down growing
        s->top 	       	= (stype == eARRAY_STACK_DOWN) ? max_size : -1;

	// Bind stack routines and create stack space based on stack type
	s->push 	= stack_push[stype];	
	s->pop 		= stack_pop[stype];	
	s->peek 	= stack_peek;	
	s->full 	= is_stack_full;
	s->empty	= is_stack_empty;
	s->len	 	= stack_size;

	// Create link list or array depending on type of stack
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
#if 0
	s->print_data	= prm->print_data;
	s->free 	= prm->free;
#else

	s->free 	= FREE_MEM;
	switch(dtype)
	{
		case eINT8:
			//char list;
			s->print_data = print_char;
			break;
		case eINT32:
			//int list;
			s->print_data = print_int;
			break;
		case eFLOAT:
			//float list;
			s->print_data = print_float;
			break;
		case eSTRING:
			//string list;
			s->print_data = print_str;
			break;
	}
#endif			
        return (t_gen) s;
}

/*! @brief  
 *   Destroy instance of the stack
 *  @param d    - Pointer to instance of stack 
 *  @return 	- NA
 * */
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


/*! @brief  
 *  Check stack full 
 *  @param d    - Pointer to instance of stack 
 *  @return 	- true if full
*/
bool is_stack_full(t_gen d)
{
	return ((t_stack*)d)->count >= ((t_stack*)d)->max_size;
}

/*! @brief  
 *  Check stack empty 
 *  @param d    - Pointer to instance of stack 
 *  @return 	- true if empty 
*/
bool is_stack_empty(t_gen d)
{
	return ((t_stack*)d)->count == 0;
}

/*! @brief  
 *  get stack size
 *  @param d    - Pointer to instance of stack 
 *  @return 	- size of stack
*/
int stack_size(t_gen d)
{
	return ((t_stack*)d)->count;
}

/*! @brief  
 *  Push an element into up growing stack
 *  @param d    - Pointer to instance of stack 
 *  @param data - Pointer to the data to be pushed
 *  @return 	- Null is stack full else data pointer
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

/*! @brief  
 *  return the top element from up growing stack
*/
t_gen stack_peek(t_gen d)
{
	t_stack *s = (t_stack*)d; 
	t_gen data = NULL;

	if (s->count == 0) {
		LOG_WARN("STACKS", "%s: Stack empty\n",s->name);
		return data;
	}
	
	// get and return the elem on top of the stack
	data = s->data[(s->top)];

	return data;
}

/*! @brief  
 *  Pop an element from up growing stack
 *  @param d    - Pointer to instance of stack 
 *  @return 	- Null if stack empty else data pointer
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

/*! @brief  
 *  Push an element into down growing stack
 *  @param d    - Pointer to instance of stack 
 *  @param data - Pointer to the data to be pushed
 *  @return 	- Null if stack Full else data pointer
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

/*! @brief  
 *  Pop an element from down growing ll stack
 *  @param d    - Pointer to instance of stack 
 *  @return 	- Null if stack empty else data pointer
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

/*! @brief  
 *  Push an element into a link list based stack
 *  @param d    - Pointer to instance of stack 
 *  @param data - Pointer to the data to be pushed
 *  @return 	- Null if stack Full else data pointer
*/
t_gen push_stack_ll(t_gen d, t_gen data)
{	
	t_stack *s = (t_stack*)d;
	t_linklist * l = (t_linklist *)s->data;
	
	// Return id stack full
	if (s->count >= s->max_size) {
		LOG_WARN("STACKS", "%s: Stack Full\n",s->name);
		return NULL;
	}

  // add in begining of the link list
	l->add(l, data);
	s->count++;

	return data;
}

/*! @brief  
 *  Pop an element from a link list based stack
 *  @param d    - Pointer to instance of stack 
 *  @return 	- Null if stack empty else data pointer
*/
t_gen pop_stack_ll(t_gen d)
{	
	t_stack *s = (t_stack*)d; 
	t_gen data = NULL;
	t_linklist * l = (t_linklist *)s->data;

	if (s->count == 0) {
		LOG_WARN("STACKS", "%s: Stack empty\n",s->name);
		return data;
	}

  // deleting the head node of link list i.e top of stack
  data = l->del_idx(l, 0);
	s->count--;

	return data;
}

/*! @brief  
 *  print_stack_info
 *  @param d    - Pointer to instance of stack 
 *  @return 	- NA
*/
void print_stack(t_gen d)
{
	t_stack *s = (t_stack*)d;
	t_linklist *l = NULL;
	int i;

	printf("%s {max: %d} {size: %d} {top: %d} {type: %s} \n[",s->name,
			s->max_size, s->count, s->top, get_name(s->type));
	
	if (s->type != eLL_STACK) {
		i = (s->type != eARRAY_STACK_DOWN)? 0:(s->max_size-1);
		do {
			s->print_data(s->data[i]);
			printf(", ");
			(s->type != eARRAY_STACK_DOWN)? i++:i--;
		} while(i != s->top);
		s->print_data(s->data[i]);
		printf("]\n");
	}
	else {
	  l = (t_linklist *)s->data;
		l->print(l);
	}
}

/*  @brief
 *  sneak peek into an element of the stack
 *  @param d    - Pointer to instance of stack 
 *  @param idx  - Index of the element to peek
 *  @return 	- Data pointer if index in bounds else NULL
*/
t_gen peek_stack(t_gen d,int idx)
{
  t_stack *s = (t_stack *)d;
	

	if (idx >= s->count) {
	  if (s->count == 0) {
		  LOG_WARN("STACKS", "The given stack is empty, attempting to peek on an empty stack :(");
		}
		else {  
		  LOG_WARN("STACKS", "The given index is out of bounds, the actual size = %d\n", s->count);
		}
		return NULL;
  }
  return NULL;
}

/*  @brief
 *  Util function to get type of stack in string
 *  @param type  - Stack Type
 *  @return String of stack type
*/
char * get_name(e_stacktype type)
{
	switch(type) {
		case eARRAY_STACK:
			return "ARRAY_STACK_UP";
		case eARRAY_STACK_DOWN:
			return "ARRAY_STACK_DOWN";
		case eLL_STACK:
			return "LL_STACK";
	}

	return "UNDEFINED";
}

