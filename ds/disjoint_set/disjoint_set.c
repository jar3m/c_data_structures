/*! @file disjoint_set.c
    @brief 
    Contains definitions of routines supported by disjoint_set
*/
#include "disjoint_set.h"

void destroy_disjoint_set(t_gen d);
void disjoint_set_make (t_gen d);
int disjoint_set_find(t_gen d, int x);
int disjoint_set_merge (t_gen d, int x, int y);
void disjoint_set_print (t_gen d);


/*! @brief  
 *  Create an instance of  disjoint set data struct
 *  @param name - Name of disjoint set instance
 *  @param size - size of the disjoin set
 *  @return     - Pointer to instance of disjoint set
 * */
t_gen create_disjoint_set(char *name, int size)
{
	t_disjset *set = get_mem(1, sizeof(t_disjset));

	set->name    = name;
	set->size    = size;
	set->subset  = get_mem(size, sizeof(t_dsetnode));

	set->make    = disjoint_set_make; 
	set->find    = disjoint_set_find;
	set->merge   = disjoint_set_merge;
	
	set->print   = disjoint_set_print;
	set->destroy = destroy_disjoint_set;

	return set;
}

/*! @brief  
 *  Destroy the instance of  disjoint set data struct
 *  @param d    - Pointer to instance of disjoint set
 *  @return     - NA
 * */
void destroy_disjoint_set(t_gen d)
{
	t_disjset *set = (t_disjset*)d;

	free_mem(set->subset);
	free_mem(set);
}

/*! @brief  
 *  The MakeSet operation adds a new element
 *  @param d    - Pointer to instance of disjoint set
 *  @return     - NA
 * */
void disjoint_set_make (t_gen d)
{
	t_disjset *set = (t_disjset*)d;

	for(int i = 0; i < set->size; i++) {
		set->subset[i].size   = 1; 
		set->subset[i].parent = i; 
	}
}

/*! @brief  
 *  Find the set the node belongs to 
 *  the method defined follows path halving
 *  @see https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 *  @param d    - Pointer to instance of disjoint set
 *  @param x    - idx of node
 *  @return     - return the root element of the disjoint set
 * */
int disjoint_set_find(t_gen d, int x)
{
	t_disjset *set = (t_disjset*)d;
	int parent = set->subset[x].parent;
	while (parent != x) {
		parent = set->subset[x].parent;
		set->subset[x].parent = set->subset[parent].parent;
		x =  set->subset[x].parent;
	}

	return x;
}

/*! @brief  
 *  Merge the given two subsets
 *  @see https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 *  @param d    - Pointer to instance of disjoint set
 *  @param x    - idx of first node
 *  @param y    - idx of second node
 *  @return     - if nodes already merged return -1 else 0 on merge
 * */
int disjoint_set_merge (t_gen d, int x, int y)
{
	t_disjset *set = (t_disjset*)d;

	x = set->find(set, x);
	y = set->find(set, y);

	if (x == y) {
		return -1;
	}
	
	if (set->subset[x].size < set->subset[y].size) {
		set->subset[x].parent = y;
		set->subset[x].size += set->subset[y].size; 
	}
	else {
		set->subset[y].parent = x;
		set->subset[y].size += set->subset[x].size; 
	}
	
	return 0;
}

/*! @brief  
 *   Print the elem of the disjoint set
 *  @param d    - Pointer to instance of link list 
 *  @return 	- NA
 * */
void disjoint_set_print (t_gen d)
{
	t_disjset *set = (t_disjset*)d;


	for(int i = 0; i < set->size; i++) {
		printf("[%d: %d %d] ",i, set->subset[i].parent, 
				set->subset[i].size);
	}
	printf("\n");
}
