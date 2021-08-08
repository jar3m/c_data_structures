/*! @file test.c
    @brief 
    Contains sample use cases/test of different data structure operations
*/

#include "common.h"
#include "link_list.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"
#include "tree.h"
#include "graph.h"
#include "array.h"
#include "disjoint_set.h"

void test_disjoint_set();
void test_graph();
void test_array();
void test_tree();
void test_heap();
void test_queue();
void test_stack();
void test_linklist();

/*! @brief  
 *   Main Driver test
 *  @param argc - Count cmd line arguments
 *  @param argv - Pointer to cmd line arguments
 *  @return 	- 0 on succesfull exit
 */
int main(int argc, char *argv[])
{
	size_t size = 0;
	int *ptr[100];
	int i;	

	mem_init();
	logger_init();
	fault_manager_init(NULL);

	for (i = 0; i < 100; i ++) {
		ptr[i] = (int *)get_mem(1, sizeof(int));
		size += sizeof(*(ptr[i]));
	}
	printf("size of allocated memory = %lu\n" , size);
	for (i = 0; i < 100; i++) {
		free_mem(ptr[i]);
	}


	LOG_ERROR("COMMON", "Hello World\n");
	LOG_WARN("COMMON", "Hello World\n");		
	LOG_INFO("COMMON", "Hello World\n");		
	LOG_DEBUG("COMMON", "Hello World\n");		
	LOG_TRACE_IN("COMMON", "Hello World\n");
	LOG_TRACE_OUT("COMMON", "Hello World\n");
	
	test_linklist();
	test_stack();
	test_queue();
	test_heap();
	test_tree();
	test_disjoint_set();
	test_graph();
	test_array();

	mem_finit();

	return 0;

}

/*! @brief  
 *   Test stack routines
 *  @return NA
 */
void test_stack()
{
	char c,*cp;
	float f,*fp;
	int *ip,i;
	t_dparams dp;
	t_stack *s1, *s2, *s3, *s4;

	// Create an array based stack to store int elements
	init_data_params(&dp, eINT32);
	s1 = create_stack("Up Stack", 10, eARRAY_STACK, &dp);

	// Create an array based stack to store char elements
	init_data_params(&dp, eINT8);
	s2 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, &dp);

	// Create an array based stack to store float elements
	init_data_params(&dp, eFLOAT);
	s3 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, &dp);

	// Create a link list based stack to store float elements
	init_data_params(&dp, eFLOAT);
	s4 = create_stack("Up Stack LL", 10, eLL_STACK, &dp);

	// Push elements to stack
	for(i = 0; i < 10; i++) {
		// Create memory for elements before adding to stack 
		s1->push(s1, assign_int(i));
		c= 'c' + i;
		s2->push(s2, assign_char(c));
		f= (float)i+0.222 / 2.0f;
		s3->push(s3, assign_float(f));
		s4->push(s4, assign_float(f));
	}
	// print stack contents
	s1->print(s1);
	s2->print(s2);
	s3->print(s3);
	s4->print(s4);
	
	// Pop elements out of the stack
	for(i = 0; i < 4; i++) {
		// Free the memory created for elements before being pushed to stack
		ip = s1->pop(s1);
		free_mem(ip);
		cp = s2->pop(s2);
		free_mem(cp);
		fp = s3->pop(s3);
		free_mem(fp);
		fp = s4->pop(s4);
		free_mem(fp);
	}
	// print stack contents
	s1->print(s1);
	s2->print(s2);
	s3->print(s3);
	s4->print(s4);

	// Push elements to stack	
	for(i = 4; i > 0; i--) {
		s1->push(s1, assign_int(i));
		c= 'c' + i;
		s2->push(s2, assign_int(c));
		f= (float)i+0.222 / 2.0f;
		s3->push(s3, assign_float(f));
		s4->push(s4, assign_float(f));
	}
	// print stack contents
	s1->print(s1);
	s2->print(s2);
	s3->print(s3);
	s4->print(s4);

	// Destroy stack
	s1->destroy(s1);
	s2->destroy(s2);
	s3->destroy(s3);
	s4->destroy(s4);
}

/*! @brief  
 *   Test link list routines
 *  @return NA
 */
void test_linklist()
{
	char c,*cp,*sp,str[][64] = {"I", "See", "Everyting"};
	float f,*fp;
	int *ip, i;
	t_dparams dp;
	t_linklist *l1, *l2, *l3, *l4, *l5;

	// Create a double link list to store int elements
	init_data_params(&dp, eINT32);
	l1 = create_link_list("INT DLL",eDOUBLE_LINKLIST, &dp);

	// Create a single link list to store char elements
	init_data_params(&dp, eINT8);
	l2 = create_link_list("CHAR SLL",eSINGLE_LINKLIST, &dp);

	// Create a single circular link list to store float elements
	init_data_params(&dp, eFLOAT);
	l3 = create_link_list("FLOAT SCLL",eSINGLE_CIRCULAR_LINKLIST, &dp);

	// Create a doubly circular link list to store string elements
	init_data_params(&dp, eSTRING);
	l4 = create_link_list("STRING DCLL",eDOUBLE_CIRCULAR_LINKLIST, &dp);

	// Create a xor link list to store float elements
	init_data_params(&dp, eFLOAT);
	l5 = create_link_list("FLOAT XORLL",eXOR_LINKLIST, &dp);

	// Add elements to link list (add elemnts to begining)
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		l2->add(l2, assign_char(c));

		l1->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		l3->add(l3, assign_float(f));
		l5->add(l5, assign_float(f));

		l4->add(l4, assign_string(str[i]));
	}
	// print elements of link list
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	// find an element in the link list 
	t_gen tmp;
	tmp =	l4->find(l4, "SEe");
  	if (tmp != NULL) {
		printf("Data present \n");
	}
	else {
		printf("Data not present \n");
	}
	
	// Search and delete a given element in link list
	LOG_INFO("TEST", "deleting nodes in link list\n");
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		cp = l2->del(l2, &c);
		free_mem(cp);

		ip = l1->del(l1, &i);
		free_mem(ip);

		f= (float)i+0.222 / 2.0f;
		fp = l3->del(l3, &f);
		free_mem(fp);

		sp = l4->del(l4, &str[i]);
		free_mem(sp);

		fp = l5->del(l5, &f);
		free_mem(fp);
	}
	// print elements of link list
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	// Add elements to link list (add elemnts to tail of link list)
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		l2->append(l2, assign_char(c));

		l1->append(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		l3->append(l3, assign_float(f));

		l4->append(l4, assign_string(str[i]));
		l5->append(l5, assign_float(f));
	}
	// print elements of link list
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	// Add elements to link list (add elemnts to head of link list)
	for (i = 3; i < 13; i++) {
		c= 'c' + i;
		l2->add(l2, assign_char(c));

		l1->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		l3->add(l3, assign_float(f));
		l5->add(l5, assign_float(f));
	}
	// print elements of link list
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	// Delete the node at idx 'i'th index
	for (i = 2; i >= 0; i--) {
		cp = l2->del_idx(l2, i);
		free_mem(cp);

		ip = l1->del_idx(l1, i);
		free_mem(ip);

		fp = l3->del_idx(l3, i);
		free_mem(fp);

		sp = l4->del_idx(l4, i);
		free_mem(sp);
		
		fp = l5->del_idx(l5, i);
		free_mem(fp);
	}
	// print elements of link list
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	// Destroy link list
	l1->destroy(l1);
	l2->destroy(l2);
	l3->destroy(l3);
	l4->destroy(l4);
	l5->destroy(l5);
}

/*! @brief  
 *   Test Queue routines
 *  @return NA
 */
void test_queue()
{
	char c,*cp;
	float f,*fp;
	int i;
	t_dparams dp;
	t_queue *q1, *q2;

	// Create a queue to store char elements
	init_data_params(&dp, eINT8);
	q1 = create_queue("Queue1", 10, eARRAY_QUEUE_CIRC, &dp);

	// Create a queue to store float elements
	init_data_params(&dp, eFLOAT);
	q2 = create_queue("Queue2", 10, eLL_QUEUE_CIRC, &dp);

	// add elements to queue
	for(i = 0; i < 10; i++) {
		c= 'c' + i;
		q1->enq(q1, assign_char(c));

		f= (float)i+0.222 / 2.0f;
		q2->enq(q2, assign_float(f));
	}
	// Print elements in queue
	q1->print(q1);
	q2->print(q2);
	
	// Dequeue or delete queue elements 
	for(i = 0; i < 10; i++) {
		cp = q1->deq(q1);
		free_mem(cp);
		fp = q2->deq(q2);
		free_mem(fp);
	}
	// Print elements in queue
	q1->print(q1);
	q2->print(q2);

	// add elements to queue
	for(i = 0; i < 4; i++) {
		c= 'c' + i;
		q1->enq(q1, assign_char(c));
		f= (float)i+0.222 / 2.0f;
		q2->enq(q2, assign_float(f));
	}
	printf("\n");

	// Print elements in queue
	q1->print(q1);
	q2->print(q2);
	
	// Peek element of the queue
	fp = q2->peek(q2, 2);
	printf("peeking idx <2: %f>\n", *fp);

	// Destroy queue
	q1->destroy(q1);
	q2->destroy(q2);
}

/*! @brief  
 *   Test Heap routines
 *  @return NA
 */
void test_heap()
{
	float f, arr1[10]={0};
	int arr[10] = {1,53,32,43,3,23,11,209, -2, 25};
	char carr[10] = {'&', '^', 'j', 'a', 'r', 'e', 'm', '*', '%', '!'};
	t_dparams dp;
	t_heap *h1, *h2, *h3;

	// Create a int heap
	init_data_params(&dp, eINT32);
	h1 = create_heap("INT HEAP", arr,10, eMIN_HEAP, &dp);

	// Create a char heap
	init_data_params(&dp, eINT8);
	h2 = create_heap("CHAR HEAP", carr,10, eMAX_HEAP, &dp);

	// Create a float heap
	init_data_params(&dp, eFLOAT);
	h3 = create_heap("float HEAP", arr1,10, eMIN_HEAP, &dp); 
	
	// Insert element
	f = -1.2234f;
	h3->insert(h3,&f);
	f = -10.3242f;
	h3->insert(h3,&f);
	f = 1000.2f;
	h3->insert(h3,&f);
	f = 1.2f;
	h3->insert(h3,&f);
	f = -9.2f;
	h3->insert(h3,&f);
	f = 9.2f;
	h3->insert(h3,&f);
	
	// heap sort data;
	printf("Sorting\n");
	h1->sort(h1);
	h2->sort(h2);

	
	// Print heap contents
	h1->print(h1);
	h2->print(h2);
	h3->print(h3);

	// heapify array
	h1->build(h1);
	h2->build(h2);
	
	// Update key
	f = 2000.01f;
	h3->update(h3, &f, 2);
	printf("Heapify'd array\n");
	f = -2000.01f;
	h3->update(h3, &f, 2);
	
	// Extract Min from heap
	printf("%d\n", *(int*)(h1->extract(h1)));
	printf("%d\n", *(int*)(h1->extract(h1)));
	
	// Print heap contents
	h1->print(h1);
	h2->print(h2);
	h3->print(h3);

	// Destroy heap
	h1->destroy(h1);
	h2->destroy(h2);
	h3->destroy(h3);

}

/*! @brief  
 *   Test Tree routines
 *  @return NA
 */
void test_tree()
{
	char c,*cp,str[][64] = {"I", "See", "Everyting"};
	char carr[10] = {'&', '^', 'j', 'a', 'r', 'e', 'm', '*', '%', '!'};
	float f,*fp;
	int i;
	t_dparams dp;
	t_tree_node *max, *min, *pred, *succ;
	t_tree *t1, *t2, *t3, *t4;

	// Create a BST tree to store character values 
	init_data_params(&dp, eINT8);
	t1 = create_tree("tree1", eBST, &dp);

	// Create a AVL tree to store float values 
	init_data_params(&dp, eFLOAT);
	t2 = create_tree("tree2", eAVL, &dp);

	// Create a AVL tree to store STRING values 
	init_data_params(&dp, eSTRING);
	t3 = create_tree("tree3", eAVL, &dp);

	// Create a BST tree to store float values 
	init_data_params(&dp, eFLOAT);
	t4 = create_tree("tree4", eBST, &dp);
	
	// Insert elements to trees
	for(i = 0; i < 3; i++) {
		// Dynammically alocate memory and store the variable to tree
		t1->insert(t1, assign_char(carr[i]));
		f= (float)i+0.222 / 2.0f;
		t2->insert(t2, assign_float(f));
		t3->insert(t3, assign_string(str[i]));
		t4->insert(t4, assign_float(f));
	}

	// Insert elements to trees
	for(i = 9; i >= 3; i--) {
		t1->insert(t1, assign_char(carr[i]));
		f= (float)i+0.222 / 2.0f;
		t2->insert(t2, assign_float(f));
		t4->insert(t4, assign_float(f));
	}

	// Find an element in tree
	char str1[10] = "some";
	if (t3->find(t3, str1) == NULL) {
		printf("%s not present in tree\n", str1);
	} else {
		printf("%s present in tree\n", str1);
	}

	// Find an element in tree
	char str2[10] = "I";
	if (t3->find(t3, str2) == NULL) {
		printf("%s not present in tree\n", str2);
	} else {
		printf("%s present in tree\n", str2);
	}
	
	// Min  Max node in tree
	printf("\nmin & max\n");
	max = t1->max(t1->root);
	min = t1->min(t1->root);
	printf("%c %c\n", *(char*) max->key, *(char*)min->key); 

	max = t2->max(t2->root);
	min = t2->min(t2->root);
	printf("%f %f\n", *(float*)max->key,*(float*)min->key); 

	max = t3->max(t3->root);
	min = t3->min(t3->root);
	printf("%s %s\n", (char*)max->key, (char*) min->key); 

	// Succ & pred in tree
	printf("\nPred & Succ\n");
	c = 'm';
	pred = t1->pred(t1,&c);
	succ = t1->succ(t1,&c);
	printf("%c %c\n", *(char*) pred->key, *(char*)succ->key); 

	f = 2.111000f;
	pred = t2->pred(t2,&f);
	succ = t2->succ(t2,&f);
	printf("%f %f\n", *(float*) pred->key, *(float*)succ->key); 
	
	pred = t3->pred(t3,str[0]);
	succ = t3->succ(t3,str[0]);
	printf("%s %s\n", (char*) pred->key, (char*)succ->key); 
	
	// Get height of the tree 
	pred = t2->root;
	succ = t4->root;
	printf("Tree height avl/bst %d %d\n",
			t2->height(pred), t4->height(succ));
	// Inorder traverse the tree nodes
	t1->inorder(t1);
	t2->inorder(t2);
	t3->inorder(t3);
	t4->inorder(t4);

	// preorder traverse the tree nodes
	t1->preorder(t1);
	t2->preorder(t2);
	t3->preorder(t3);
	t4->preorder(t4);

	// postorder traverse the tree nodes
	t1->postorder(t1);
	t2->postorder(t2);
	t3->postorder(t3);
	t4->postorder(t4);

	// Print the tree nodes
	t1->print(t1);
	t2->print(t2);
	t3->print(t3);
	t4->print(t4);

	// deleting nodes
	for(i = 9; i >= 0; i--) {
		cp = t1->del(t1, &carr[i]);
		free_mem(cp);
		f= (float)i+0.222 / 2.0f;
		fp = t2->del(t2, &f);
		free_mem(fp);
	}

	t1->destroy(t1);
	t2->destroy(t2);
	t3->destroy(t3);
	t4->destroy(t4);
}

/*! @brief  
 *   Test Graph routines
 *  @return NA
 */
void test_graph()
{
	t_graph *g1, *g2, *g3, *g4, *g5;
	char city[][64] ={"Delhi", "Bangalore","Chennai"}; 
	int i, *ip, num[] = {1,2,3,4,5,6,7,8,9,10};
	int a1[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int a2[] = {1,2,3,4,5,6,7,8,9,10};
	int a3[] = {1,2,3,4,5,6,7,8,9,10};
	t_dparams dp;
	t_bfsinfo *bfs;	
	t_dfsinfo *dfs;	
	t_daginfo *dag;	

	// create data opertation set of type 'String' 
	init_data_params(&dp, eSTRING);
	// Dummy free since the elements are part of an array and not dynamically allocated
	dp.free = dummy_free;
	// Create a graph to store strings
	g1 = create_graph("Graph 1", 10, &dp);

	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	g2 = create_graph("Graph 2", 10, &dp);

	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	g3 = create_graph("Graph 3", 12, &dp);

	// create data opertation set of type 'int' 
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	g4 = create_graph("Graph 4", 10, &dp);

	// create data opertation set of type 'int' 
	init_data_params(&dp, eINT32);
	// Dummy free since the elements are part of an array
	dp.free = dummy_free;
	// Create a graph to store int values
	g5 = create_graph("Graph 5", 10, &dp);

	// Create symmetric edges between vertices
	g1->add_wedge_sym(g1, city[0], city[1], 420);   
	g1->add_wedge_sym(g1, city[1], city[2], 1234);   
	g1->add_wedge(g1, city[2], city[0], 1000);   
	g1->wprint(g1);

	// Check whether the edge between two vertices exist?
	if (g1->has_edge(g1, city[0], city[2]) == NULL) {
		printf("%s not linked to %s\n",city[0],city[1]);
	} else {
		printf("%s linked to %s\n",city[0],city[1]);
	} 

	// Delete the directed edge between two nodes
	g1->del_edge(g1, city[0], city[1]);  

	// Delete an undirected edge between two nodes
	g1->del_edge_sym(g1, city[2], city[1]);  
	g1->wprint(g1);

	// Delete a Vertex from graph
	g1->del_vertex(g1, city[2]);
	g1->wprint(g1);

	if (g1->find(g1, city[2]) == NULL) {
		printf("%s not present in graph\n",city[2]);
	} else {
		printf("%s present in graph\n",city[2]);
	} 
	// weighted print graph
	g1->wprint(g1);

	printf("**************\n");

	printf("- Connected Components -\n");

	// Add nodes to graph
	for (i = 0; i < 12; i++) {
		g3->add_vertex(g3, &a1[i]);   
	}

	// Create symmetric edges between vertices
	g3->add_edge_sym(g3, &a1[0], &a1[1]);   
	g3->add_edge_sym(g3, &a1[0], &a1[4]);   
	g3->add_edge_sym(g3, &a1[4], &a1[8]);   
	g3->add_edge_sym(g3, &a1[4], &a1[9]);   
	g3->add_edge_sym(g3, &a1[2], &a1[3]);   
	g3->add_edge_sym(g3, &a1[2], &a1[6]);   
	g3->add_edge_sym(g3, &a1[2], &a1[7]);   
	g3->add_edge_sym(g3, &a1[3], &a1[7]);   
	g3->add_edge_sym(g3, &a1[6], &a1[7]);   
	g3->add_edge_sym(g3, &a1[6], &a1[10]);   
	g3->add_edge_sym(g3, &a1[7], &a1[10]);   
	g3->add_edge_sym(g3, &a1[7], &a1[11]);   
	g3->add_edge_sym(g3, &a1[8], &a1[9]);   
	g3->print(g3);
	
	// Run BFS on GRAPH
	printf("- BFS -\n");
	bfs  = g3->bfs(g3, &a1[0]);

	// Display the BFS Tree
	for(i = 0; i < 12; i++) {
		ip = (int*)bfs[i].parent;
		printf("%d: %d %d %d\n", 
			bfs[i].comp,i+1, bfs[i].level, ip != NULL? *ip: -1);
	}
	free_mem(bfs);
	
	// Run DFS on GRAPH
	printf("- DFS -\n");
	dfs  = g3->dfs(g3, &a1[0]);

	// Display the DFS Tree
	for(i = 0; i < 12; i++) {
		ip = (int*)dfs[i].parent;
		printf("%d: %d %d {%d %d}\n", 
			dfs[i].comp, i+1, ip != NULL? *ip: -1, dfs[i].pre, dfs[i].post);
	}
	free_mem(dfs);

	// Add nodes to graph
	for (i = 0; i < 8; i++) {
		g4->add_vertex(g4, &a2[i]);   
	}
	
	// Create asymmetric edges
	g4->add_edge(g4, &a2[0], &a2[2]);   
	g4->add_edge(g4, &a2[0], &a2[3]);   
	g4->add_edge(g4, &a2[0], &a2[4]);   
	g4->add_edge(g4, &a2[1], &a2[2]);   
	g4->add_edge(g4, &a2[1], &a2[7]);   
	g4->add_edge(g4, &a2[2], &a2[5]);   
	g4->add_edge(g4, &a2[3], &a2[7]);   
	g4->add_edge(g4, &a2[3], &a2[5]);   
	g4->add_edge(g4, &a2[4], &a2[7]);   
	g4->add_edge(g4, &a2[5], &a2[6]);   
	g4->add_edge(g4, &a2[6], &a2[7]);   
	g4->print(g4);
	
	printf("- DAGS Sorting and Longest Path -\n");
	dag = g4->topo_order_dag(g4);

	// Display the longest path and ordered/sorted edges of the DAG
	for(i = 0; i < 8; i++) {
		ip = (int*)dag[i].node;
		printf("{%d %d}\n", 
			ip != NULL? *ip: -1, dag[i].longest_path);
	}
	free_mem(dag);

	// Add nodes to graph
	for (i = 0; i < 10; i++) {
		g2->add_vertex(g2, &num[i]);   
	}

	// Create symmetric weighted edges
	g2->add_wedge_sym(g2, &num[0], &num[1], 10);   
	g2->add_wedge_sym(g2, &num[0], &num[2], 80);   
	g2->add_wedge_sym(g2, &num[1], &num[2], 6);   
	g2->add_wedge_sym(g2, &num[2], &num[3], 70);   
	g2->add_wedge_sym(g2, &num[1], &num[4], 20);   
	g2->add_wedge_sym(g2, &num[4], &num[5], 50);   
	g2->add_wedge_sym(g2, &num[4], &num[6], 10);   
	g2->add_wedge_sym(g2, &num[5], &num[6], 5);   
	g2->wprint(g2);

	// Run Dijkstra's algo for src node '1'
	printf("* Dijkstra's Algo *\n");
	t_distinfo *dist = dijkstra(g2, &num[0]);

	// Display the Distance table with parent node and cost from src
	for (i = 0; i < 10; i++) {
		printf("{%d : %d %d}\n", 
			dist[i].edge.node?((t_gnode*)dist[i].edge.node)->idx+1: -1,
			dist[i].edge.weight,
			dist[i].parent? ((t_gnode*)dist[i].parent)->idx+1: -1);
	}
	free_mem(dist);

	// Run Prim's MST algo
	printf("* Prim's Minimum Spanning Tree *\n");
	dist = prims_mst(g2);

	// Display the Prim's MST 
	for (i = 0; i < 10; i++) {
		printf("{%d - %d: %d}\n", 
			dist[i].edge.node?((t_gnode*)dist[i].edge.node)->idx+1: -1,
			dist[i].parent? ((t_gnode*)dist[i].parent)->idx+1: 
			-1, dist[i].edge.weight);
	}
	free_mem(dist);
	
	// Run Kruskal's MST algo
	printf("* Kruskal's Minimum Spanning Tree *\n");
	dist = kruskals_mst(g2);

	// Display the Kruskal MST 
	for (i = 0; i < 10; i++) {
		printf("{%d - %d: %d}\n", 
			dist[i].edge.node?((t_gnode*)dist[i].edge.node)->idx+1: -1,
			dist[i].parent? ((t_gnode*)dist[i].parent)->idx+1: 
			-1, dist[i].edge.weight);
	}
	free_mem(dist);


	// Add nodes to graph
	for (i = 0; i < 10; i++) {
		g5->add_vertex(g5, &a3[i]);   
	}

	// Add nodes to graph
	g5->add_wedge(g5, &a3[0], &a3[1], 10);   
	g5->add_wedge(g5, &a3[0], &a3[7], 8);   
	g5->add_wedge(g5, &a3[1], &a3[5], 2);   
	g5->add_wedge(g5, &a3[2], &a3[1], 1);   
	g5->add_wedge(g5, &a3[2], &a3[3], 1);   
	g5->add_wedge(g5, &a3[3], &a3[4], 3);   
	g5->add_wedge(g5, &a3[4], &a3[5], -1);   
	g5->add_wedge(g5, &a3[5], &a3[2], -2);   
	g5->add_wedge(g5, &a3[6], &a3[5], -1);   
	g5->add_wedge(g5, &a3[6], &a3[1], -4);   
	g5->add_wedge(g5, &a3[7], &a3[6], 1);   
	g5->wprint(g5);

	// Bellman Ford shortest path src node as 0
	dist = bellman_ford(g5, &a3[0]);

	printf("* Bellman Ford *\n");
	// print the distance
	for (i = 0; i < 10; i++) {
		printf("{%d : %d %d}\n", 
			dist[i].edge.node?((t_gnode*)dist[i].edge.node)->idx+1: -1,
			dist[i].edge.weight,
			dist[i].parent? ((t_gnode*)dist[i].parent)->idx+1: -1);
	}
	free_mem(dist);

	// destroy graph
	g1->destroy(g1);
	g2->destroy(g2);
	g3->destroy(g3);
	g4->destroy(g4);
	g5->destroy(g5);
}

/*! @brief  
 *   Test Array search and sort routines
 *  @return NA
 */
void test_array()
{
	int a1[] = {310,-22,35,534,55,76,907,8,239,1210,151,-12};
	int a2[] = {310,-22,35,534,55,76,907,8,239,1210,151,-12};
	int a3[] = {310,-22,35,534,55,76,907,8,239,1210,151,-12};
	t_dparams dp;

	// Create operating fn depending on type of data
	init_data_params(&dp, eINT32);

	// select sort array
	selection_sort(a1, 12, &dp);

	printf("Select sort: \n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", a1[i]);
	}
	printf("\n");

	// insertion sort array
	insertion_sort(a2, 12, &dp);

	printf("Insertion sort: \n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", a2[i]);
	}
	printf("\n");

	// quick sort array
	quick_sort(a3, 12, &dp);

	printf("quick sort: \n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", a3[i]);
	}
	printf("\n");


}

/*! @brief  
 *   Test Disjoint set routines (Merge-Find)
 *  @return NA
 */
void test_disjoint_set()
{
	// Create a disjoint set
	t_disjset *d = create_disjoint_set("disjoint set", 10);

	printf("* Disjoint set operation test *\n");
	
	// Make set i.e, every elem point to self as it component
	d->make(d);

	// merge two components
	d->merge(d, 1, 2);
	d->merge(d, 4, 3);
	d->merge(d, 3, 2);
	d->merge(d, 5, 7);
	
	// print set
	d->print(d);

	// find the component the element belongs to
	printf("find 2: %d\n",d->find(d, 2));
	printf("find 1: %d\n",d->find(d, 4));
	printf("find 8: %d\n",d->find(d, 8));
	// print set
	d->print(d);

	// Destroy disjoint set
	d->destroy(d);
}
