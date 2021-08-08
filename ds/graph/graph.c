/*! @file graph.c
    @brief 
    Contains definitions of routines supported by graph
    @author Meraj
*/
#include "graph.h"
#include "link_list.h"
#include "queue.h"
#include "stack.h"
#include "heap.h"
#include "disjoint_set.h"
#include "array.h"

// function Declarations
t_gen graph_delete(t_gen,t_gen);
t_gen graph_find(t_gen,t_gen);
int graph_len(t_gen);
t_gen graph_add_vertex(t_gen d, t_gen data);
t_gen graph_has_edge(t_gen d, t_gen n1, t_gen n2);
t_gen graph_add_edge(t_gen d, t_gen n1, t_gen n2);
t_gen graph_del_edge(t_gen d, t_gen n1, t_gen n2);
t_gen graph_add_edge_sym(t_gen d, t_gen n1, t_gen n2);
t_gen graph_del_edge_sym(t_gen d, t_gen n1, t_gen n2);
t_gen graph_del_vertex(t_gen d, t_gen n1);
t_gen graph_add_wedge(t_gen d, t_gen n1, t_gen n2, int weight);
t_gen graph_add_wedge_sym(t_gen d, t_gen n1, t_gen n2, int weight);
t_gen graph_bfs(t_gen d, t_gen n);
t_gen graph_dfs(t_gen d, t_gen n);
t_gen graph_toplogicaly_order_dag(t_gen d);
void graph_neigh_print(t_gen d, t_gen neigh);
void graph_print(t_gen d);
void graph_wprint(t_gen d);
void graph_destroy(t_gen d);

/*! @brief  
 *  Create an instance of graph
 *  @param name	 - Name of graph instance
 *  @param size  - Max vertices in graph
 *  @param prm   - Data type specific parameters
 *  @return 	 - Pointer to instance of graph
 * */
t_gen create_graph(char *name, int size, t_dparams *prm)
{
	t_graph *g = get_mem(1, sizeof(t_graph));

	// Initailze graph Params
	g->name 	  = name;
	g->count 	  = 0;
	g->total_edges    = 0;
	g->max_size       = size;
	g->nodes          = get_mem(size, sizeof(t_gnode));
	
	// Initailze graph routines
	g->add_vertex	  = graph_add_vertex; 
	g->del_vertex	  = graph_del_vertex;
	g->add_edge	  = graph_add_edge; 
	g->del_edge	  = graph_del_edge;
	g->has_edge	  = graph_has_edge;
	g->add_edge_sym   = graph_add_edge_sym; 
	g->del_edge_sym   = graph_del_edge_sym;
	g->add_wedge      = graph_add_wedge; 
	g->add_wedge_sym  = graph_add_wedge_sym; 
	g->bfs	          = graph_bfs;
	g->dfs	          = graph_dfs;
	g->topo_order_dag = graph_toplogicaly_order_dag;
	g->find 	  = graph_find;
	g->len	 	  = graph_len;
	g->print 	  = graph_print;
	g->wprint 	  = graph_wprint;
	g->destroy 	  = graph_destroy;

	// Initailze data type based operations req for prop working of graph
	g->cmpr 	  = prm->cmpr;
	g->swap 	  = prm->swap;
	g->free 	  = prm->free;
	g->print_data 	  = prm->print_data;

	return (t_gen)g;
}


/*! @brief  
 *   get num Vertex(nodes) in graph;
 *  @param d	- Pointer instance of graph
 *  @return 	- Vertex(node) Count
 */
int graph_len(t_gen g)
{
	return ((t_graph*)g)->count;
}

/*! @brief  
 *  Find a Vertex(node) in graph;
 *  @param d	- Pointer instance of graph
 *  @param data	- Pointer to data
 *  @return 	- Pointer to Vertex(node) containing data else null
 */
t_gen graph_find(t_gen d, t_gen data)
{
	t_graph *g = (t_graph*)d;
	int i;

	for (i = 0; i < g->count; i++) {
		if (g->cmpr(g->nodes[i].id, data) == eEQUAL) {
			return &g->nodes[i];
		}
	}

	return NULL;
}

/*! @brief  
 *  Util compare function for neigh link list node data
 *  @param x	- Pointer linklist node 
 *  @param y   	- Pointer to data to be compared
 *  @return 	- Equal, Less or Great
 */
e_cmpr graph_neigh_list_compare(t_gen x, t_gen y)
{
	t_gedge *neighl = (t_gedge*) x;
	t_gnode *node = (t_gnode*) y;
	
	if (neighl->node == node) {
		return eEQUAL;
	}

	return eLESS;
}

/*! @brief  
 *  Util free function for deleting neigh link list node data
 *  @param mem	- Pointer to memory
 *  @param file - File name
 *  @param line - line number
 *  @return 	- NA
 */
void graph_neigh_list_free(t_gen mem, char *file, int line)
{
	t_gedge *neighl = (t_gedge*) mem;
	
	neighl->node = NULL;
	
	free_mem(neighl);
	
}

/*! @brief  
 *  Add a Vertex(node) in graph;
 *  @param d	- Pointer instance of graph
 *  @param data	- Pointer to data
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_add_vertex(t_gen d, t_gen data)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_dparams dp;
	
	// existing node return
	node = g->find(g, data);
	if (node != NULL) {
		//LOG_WARN("GRAPH", "%s: node already present\n",g->name);
		return node;
	}

	// Graph size full
	if (g->count >=  g->max_size) {
		//LOG_WARN("GRAPH", "%s: No space left to add node in graph\n",g->name);
		return NULL;
	}

	// add node to graph
	node = &g->nodes[g->count];
	node->idx = g->count;
	g->count++;

	// create link list to store node neighbors
	node->id = data;
	init_data_params(&dp, eUSER);
	dp.free = graph_neigh_list_free;
	dp.cmpr = graph_neigh_list_compare;
//	node->neigh = create_link_list("neighNodes", eDOUBLE_LINKLIST, &dp);
	node->neigh = create_link_list("neighNodes", eXOR_LINKLIST, &dp);

	return node;
}

/*! @brief  
 *  Check edge between two Vertices(nodes) in graph;
 *  @param d	- Pointer instance of graph
 *  @param n1	- Pointer to data1
 *  @param n2	- Pointer to data2
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_has_edge(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gnode *A, *B;

	A = g->find(g, n1);
	B = g->find(g, n2);
	
	// Nodes not present
	if (A == NULL || B == NULL) {
		return NULL;
	}
	
	// return if B present A's neigh list
	return A->neigh->find(A->neigh, B);
}

/*! @brief  
 *  Add an asymmetric edge between two vertices(nodes) in graph;
 *  @param d	  - Pointer instance of graph
 *  @param n1	  - Pointer to data1
 *  @param n2	  - Pointer to data2
 *  @return 	  - Pointer to Vertex(node) else null
 */
t_gen graph_add_edge(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gnode *A, *B;
	t_gedge *edge;

	// ADD Node if node doesn't exit else get node
	A = g->add_vertex(g, n1);
	B = g->add_vertex(g, n2);

	// Return if Graph FULL
	if (A == NULL || B == NULL) {
		return NULL;
	}

	// Return Link already exists
	if (g->has_edge(g, n1, n2) != NULL) {
		return NULL;
	}

	g->total_edges++;

	edge = get_mem(1, sizeof(t_gedge));
	edge->node  = B;
	edge->weight = 0;

	// link N1->N2
	A->neigh->append(A->neigh, edge);

	return A;
}

/*! @brief  
 *  Add an asymmetric weighted edge between two vertices(nodes) in graph;
 *  @param d	  - Pointer instance of graph
 *  @param n1	  - Pointer to data1
 *  @param n2	  - Pointer to data2
 *  @param weight - Edge weight
 *  @return 	  - Pointer to Vertex(node) else null
 */
t_gen graph_add_wedge(t_gen d, t_gen n1, t_gen n2, int weight)
{
	t_graph *g = (t_graph*)d;
	t_gnode *A, *B;
	t_gedge *edge;

	// ADD Node if node doesn't exit else get node
	A = g->add_vertex(g, n1);
	B = g->add_vertex(g, n2);

	// Return if Graph FULL
	if (A == NULL || B == NULL) {
		return NULL;
	}

	// Return Link already exists
	if (g->has_edge(g, n1, n2) != NULL) {
		return NULL;
	}

	g->total_edges++;

	edge = get_mem(1, sizeof(t_gedge));
	edge->node  = B;
	edge->weight = weight;

	// link N1->N2
	A->neigh->append(A->neigh, edge);

	return A;
}

/*! @brief  
 *  Del an asymmetric edge between two vertices(nodes) in graph;
 *  @param d	- Pointer instance of graph
 *  @param n1	- Pointer to data1
 *  @param n2	- Pointer to data2
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_del_edge(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gnode *A, *B;

	A = g->find(g, n1);
	B = g->find(g, n2);
	
	// Nodes not present
	if (A == NULL || B == NULL) {
		return NULL;
	}
	
	// unlink N1->N2
	d = A->neigh->del(A->neigh, B);
	free_mem(d);
	return A;
}

/*! @brief  
 *  Add a symmetric edge between two vertices(nodes) in graph;
 *  @param d	- Pointer instance of graph
 *  @param n1	- Pointer to data1
 *  @param n2	- Pointer to data2
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_add_edge_sym(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gen ret;

	// link N1->N2
	ret = g->add_edge(g, n1, n2);
	// link N2->N1
	ret = g->add_edge(g, n2, n1);

	return ret;
}

/*! @brief  
 *  Add a symmetric weighted edge between two vertices(nodes) in graph;
 *  @param d	  - Pointer instance of graph
 *  @param n1	  - Pointer to data1
 *  @param n2	  - Pointer to data2
 *  @param weight - Edge weight
 *  @return 	  - Pointer to Vertex(node) else null
 */
t_gen graph_add_wedge_sym(t_gen d, t_gen n1, t_gen n2, int weight)
{
	t_graph *g = (t_graph*)d;
	t_gen ret;

	// link N1->N2
	ret = g->add_wedge(g, n1, n2, weight);
	// link N2->N1
	ret = g->add_wedge(g, n2, n1, weight);

	return ret;
}

/*! @brief  
 *  Del a symmetric edge between two vertices(nodes) in graph;
 *  @param d	- Pointer instance of graph
 *  @param n1	- Pointer to data1
 *  @param n2	- Pointer to data2
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_del_edge_sym(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gen ret;

	// unlink N1->N2
	ret = g->del_edge(g, n1, n2);
	
	// unlink N2->N1
	ret = g->del_edge(g, n2, n1);

}

/*! @brief  
 *  Del a vertex(node) in graph;
 *  @param d	- Pointer instance of graph
 *  @param n1	- Pointer to data1
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_del_vertex(t_gen d, t_gen n1)
{
	t_graph *g = (t_graph*)d;
	int i;
	t_gnode *A, *node;
	t_gen tmp = NULL;

	// Find node
	A = g->find(g, n1);

	// return if node doesn't exist
	if (A == NULL) {
		return tmp;
	}


	// travers all nodes in graph
	// and delete itself from each node->neigh list
	for (i = 0; i < g->count; i++) {
		if (A->idx == i) {
			continue;
		}
		node = &g->nodes[i];
		tmp = node->neigh->del(node->neigh, A);
		free_mem(tmp);
	}
	// destroy neigh list 
	A->neigh->destroy(A->neigh);	
	tmp = A->id;
	
	g->count--;
	
	if (g->count != 0 && g->count != A->idx) {
		// Swap node to be deleted with last node
		A->id = g->nodes[g->count].id;
		A->neigh = g->nodes[g->count].neigh;
	}

	return tmp;
}

/*! @brief  
 *  Breath First Search Core routine 
 *  This routine does bfs on all conncted components
 *  @param g	- Pointer instance of graph
 *  @param d	- Pointer to Source node from where to start BFS
 *  @param bfs	- Pointer to bfs info of each vertex
 *  @param q	- Pointer to queue used for BFS
 *  @param comp	- Component of the graph
 *  @return 	- NA
 */
void bfs_core(t_graph *g, t_gnode *node, t_bfsinfo *bfs, t_queue *q, int comp)
{
	t_linklist *neigh_list;
	t_llnode *cur, *end;
	t_gnode *neigh;
	t_gedge *edge;

	// Initializations 
	bfs[node->idx].level  = 0; 
	bfs[node->idx].parent = NULL; 
	bfs[node->idx].comp   = comp;
	q->enq(q, node);
	while (q->empty(q) != true) {
		node = q->deq(q);

		// For each vertex in queue
		// Increment level and update parent for each new vertex
		neigh_list = (t_linklist*)node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			edge  = cur->data;
			neigh = edge->node;
			// If neigh node not visited add neigh to queue 
			if (bfs[neigh->idx].level == -1) {
				bfs[neigh->idx].level  = bfs[node->idx].level + 1;
				bfs[neigh->idx].parent = node->id;
				bfs[neigh->idx].comp   = comp;
				q->enq(q, neigh);
			}
			// Get next node in neigh list
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
}


/*! @brief  
 *  Breath First Search
 *  BFS info Contains
 *	- Level of the vertex from Source node
 *      - Parent node of a vertex
 *      - Component of the graph that the a vertex belongs to
 *  @param d	- Pointer instance of graph
 *  @param n	- Pointer to data1 (Source node from where to start BFS)
 *  @return 	- Pointer to BFS info if node present else null
 */
t_gen graph_bfs(t_gen d, t_gen n)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_queue *q;
	t_bfsinfo *bfs = NULL;
	t_dparams dp;
	int comp;
	bool all_nodes_visited = false;

	// Find node
	node = g->find(g, n);

	// return if node doesn't exist
	if (node == NULL) {
		return bfs;
	}

	// Create queue and bfs info array for bfs 
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	q = create_queue("bfs_Q", g->count, eLL_QUEUE_CIRC, &dp);
	bfs = get_mem(g->count, sizeof(t_bfsinfo));
	
	// Init bfs data struct for vertex exploration
	for (int i = 0; i < g->count; i++) {
		bfs[i].parent = NULL;
		bfs[i].comp = bfs[i].level  = -1;
	}

	// Run BFS for different connected Components of graph
	comp = 0;
	while (all_nodes_visited == false) {
		bfs_core(g, node, bfs, q, comp);
		
		all_nodes_visited = true;

		for (int i = 0; i < g->count; i++) {
			// unvisited Vertex remains and belongs to different component
			// Run BFS with new unvisited vertex
			if (bfs[i].level == -1) {
				all_nodes_visited = false;
				node = &g->nodes[i];
				comp++;
				break;
			}
		}
	}

	q->destroy(q);
	
	return bfs;
}

/*! @brief  
 *  Depth First Search Core routine 
 *  This routine does dfs on all conncted components
 *  @param g      - Pointer instance of graph
 *  @param d      - Pointer to Source node from where to start DFS
 *  @param dfs    - Pointer to dfs info of each vertex
 *  @param s      - Pointer to stack used for DFS
 *  @param comp   - Component of the graph
 *  @param gcount - Pointer to count value that used to store pre/post(arrival/depature) of a vertex
 *  @return 	  - NA
 */
void dfs_core(t_graph *g, t_gnode *node, t_dfsinfo *dfs, t_stack *s, int comp, int *gcount)
{
	t_linklist *neigh_list;
	t_llnode *cur, *end;
	t_gnode *neigh;
	t_gedge *edge;
	int count = *gcount;
	
	dfs[node->idx].parent = NULL;
	dfs[node->idx].pre    = count++;
	dfs[node->idx].comp   = comp;
	s->push(s, node);
	do {
		neigh_list = (t_linklist*)node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		// Depth Traversal of unvisited neighbor vertex
		// Don't check Neighbor list if already all neighbors visited  
		while (cur && dfs[node->idx].visited_neighbors != 0) {
			edge  = cur->data;
			neigh = edge->node;
			// For each unvisited neighbor vertex
			// update parent and pre count 
			// Push Node to stack break for Depth Traversal
			if (dfs[neigh->idx].pre == -1) {
				dfs[neigh->idx].parent = node->id;
				dfs[neigh->idx].pre    = count++;
				dfs[neigh->idx].comp   = comp;
				s->push(s, neigh);
				node = neigh;
				break;
			} 
			// Else get next unvisited vertex in neigh list
			else {	
				// Get next unvisited node in neigh list
				cur = neigh_list->next_node(neigh_list, cur);
				
				if (cur == end) {
					// All neighbor of current node have been visited
					dfs[node->idx].visited_neighbors = 0;
					break;
				}
			}
		}
			
		node = s->pop(s);
		// Pop'd node has unvisted neighbors
		// Push node on to stack again to continue DFS for unvisited neighbors
		if (dfs[node->idx].visited_neighbors != 0 && cur) {
			s->push(s, node);
			continue;
		}
	
		// All neighbors visited update post count on exit
		dfs[node->idx].post = count++;
	} while (s->empty(s) != true);
	
	// Preserve count value for remaining nodes
	*gcount = count;
}


/*! @brief  
 *  Depth First Search
 *  DFS info contains
 *	- pre/post(arrival/depature) intervals of a vertex
 *      - Parent node of a vertex
 *      - Component of the graph that the a vertex belongs to
 *  @param d	- Pointer instance of graph
 *  @param n	- Pointer to data1 (Source node from where to start DFS)
 *  @return 	- Pointer to DFS info of all nodes if node present else null
 */
t_gen graph_dfs(t_gen d, t_gen n)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_stack *s;
	t_dfsinfo *dfs = NULL;
	t_dparams dp;
	int count, comp;
	bool all_nodes_visited = false;

	// Find node
	node = g->find(g, n);

	// return if node doesn't exist
	if (node == NULL) {
		return dfs;
	}

	// Create stack and dfs info array for dfs 
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	s = create_stack("dfs_Stack", g->count, eLL_STACK, &dp);
	dfs = get_mem(g->count, sizeof(t_dfsinfo));
	
	// Init dfs data struct for vertex exploration
	for (int i = 0; i < g->count; i++) {
		dfs[i].comp = -1;
		dfs[i].parent = NULL;
		dfs[i].pre = dfs[i].post = -1;
		dfs[i].visited_neighbors = 1;
	}

	// Run DFS for different connected Components of graph
	comp = count = 0; 
	while (all_nodes_visited == false) {
		dfs_core(g, node, dfs, s, comp, &count);
		
		all_nodes_visited = true;
		for (int i = 0; i < g->count; i++) {
			// unvisited Vertex remains and belongs to different component
			// Run DFS with new unvisited vertex
			if (dfs[i].pre == -1) {
				all_nodes_visited = false;
				node = &g->nodes[i];
				comp++;
				break;
			}
		}
	}
	s->destroy(s);
	
	return dfs;
}

/*! @brief  
 *  Depth First Search Optimised by eliminating the need for revisiting
 *  a previously visited vetex in neighbor list. 
 *  Note: These visits happen only during the scanning of neighbor list
 *  to get an unvisited node
 *  @param d	- Pointer instance of graph
 *  @param n	- Pointer to data1 (Source node from where to start DFS)
 *  @return 	- Pointer to DFS info if node present else null
 */
t_gen graph_dfs_optimised(t_gen d, t_gen n)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node, *neigh;
	t_gedge *edge;
	t_stack *s;
	t_dfsinfo *dfs = NULL;
	t_dparams dp;
	t_linklist *neigh_list;
	t_llnode *cur, *end = NULL;
	int count = 0;

	// Find node
	node = g->find(g, n);

	// return if node doesn't exist
	if (node == NULL) {
		return dfs;
	}

	// Create queue and dfs info array for dfs 
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	s = create_stack("dfs_Stack", g->count, eLL_STACK, &dp);
	dfs = get_mem(g->count, sizeof(t_dfsinfo));
	
	// Init dfs data struct for vertex exploration
	for (int i = 0; i < g->count; i++) {
		dfs[i].parent = NULL;
		dfs[i].pre = dfs[i].post = -1;
		neigh_list = (t_linklist*)(g->nodes[i].neigh);
		dfs[i].visited_neighbors = neigh_list->len(neigh_list);
	}
	
	dfs[node->idx].pre = count++;
	s->push(s, node);
	do {	
		neigh_list = (t_linklist*)node->neigh;
		cur = neigh_list->head_node(neigh_list);

		// Depth Traversal of unvisited neighbor vertex
		// Don't check Neighbor list if already visited all the neighbors
		while (cur && dfs[node->idx].visited_neighbors != 0) {
			edge  = cur->data;
			neigh = edge->node;
			dfs[node->idx].visited_neighbors--;
			// For each vertex unvisited vertex
			// update parent and pre count 
			// Push Node to stack for Depth Traversal
			if (dfs[neigh->idx].pre == -1) {
				dfs[neigh->idx].parent = node->id;
				s->push(s, neigh);
				dfs[neigh->idx].pre = count++;
				node = neigh;

				// Constant 0(1) del and append on link list
				// To ensure not visiting a previously visited vertex
				// By pushing the unvisited node to last
				// And eliminating it being revisited
				// By traversing  the list only 'visited_neighbors' times
				edge = neigh_list->del_idx(neigh_list, 0);
				neigh_list->append(neigh_list, edge);
				break;
			}  
			// Else get next unvisited vertex in neigh list
			else {	
				// Get next unvisited node in neigh list
				cur = neigh_list->next_node(neigh_list, cur);
				
				if (cur == end) {
					// All neighbor of current node have been visited
					//dfs[node->idx].visited_neighbors = true;
					break;
				}
			}
		}
			
		node = s->pop(s);
		// Pop'd node has unvisted neighbors
		// Push node on to stack again to continue DFS for unvisited neighbors
		if (dfs[node->idx].visited_neighbors != 0) {
			s->push(s, node);
			continue;
		}
	
		// All neighbors visited update post count on exit
		dfs[node->idx].post = count++;
	} while (s->empty(s) != true);

	s->destroy(s);
	
	return dfs;
}


/*! @brief
 *  Topologicaly order/Topologicaly sort the nodes of a DAG
 *  And get the longest path to each of the vertices in DAG
 *  The topologicaly order nodes instead of being printed
 *  can be pushed to link list and return
 *  @param d	 - Pointer instance of graph
 *  @return 	 - DAG info struct containg longest path 
 *                 and vertices in topological order
 */
t_gen graph_toplogicaly_order_dag(t_gen d)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node, *neigh;
	t_gedge *edge;
	t_linklist *neigh_list;
	t_llnode *cur,*end;
	t_daginfo *dag_inf;
	t_dparams dp;
	t_queue *q;

	// Create queue and array for dag_inf
	dag_inf = get_mem(g->count, sizeof(t_daginfo));
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	q = create_queue("topo_dag", g->count, eLL_QUEUE_CIRC, &dp);
	
	// Indegree initialization
	for (int i = 0; i < g->count; i++) {
		dag_inf[i].indegree     = 0;
		dag_inf[i].longest_path = 0;
	}

	// Update indegree for all nodes
	for (int i = 0; i < g->count; i++) {
		neigh_list = g->nodes[i].neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			edge = cur->data;
			node = edge->node;
			dag_inf[node->idx].indegree += 1;
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	
	// Add vertices with indegree 0
	for (int i = 0; i < g->count; i++) {
		if (dag_inf[i].indegree == 0) {
			q->enq(q, &g->nodes[i]);
		}
	}
	
	// Start exploration to sort/order by
	// Enumerating the vertices(delete/visited)
	while (q->empty(q) != true) {
		node = q->deq(q);
		// Enumerate node, i.e, mark as visited
		dag_inf[node->idx].node     =  node->id;
		dag_inf[node->idx].indegree = -1;
		
		// update longest path and indegree of neighbors
		// for the enumerated vertex
		neigh_list = node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			edge  = cur->data;
			neigh = edge->node;
			dag_inf[neigh->idx].indegree -= 1;
			// update path as max of parent and cur longest path
			dag_inf[neigh->idx].longest_path = 
				(dag_inf[neigh->idx].longest_path > dag_inf[node->idx].longest_path) ?
				dag_inf[neigh->idx].longest_path : (dag_inf[node->idx].longest_path + 1);
			
			//push to queue any neigh with indegree 0 
			if (dag_inf[neigh->idx].indegree == 0) {
				q->enq(q, neigh);
			}	
			// Get next neigh
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	
	q->destroy(q);

	return dag_inf;
}

/*! @brief  
 *  Util function to Print neighbor list of a vetex(node)
 *  @param d	 - Pointer instance of graph
 *  @param neigh - Pointer to neigh link list 
 *  @return 	 - NA
 */
void graph_neigh_print(t_gen d, t_gen neigh)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_gedge *edge;
	t_linklist *l = (t_linklist*)neigh;
	t_llnode *cur, *end;

	printf("{ ");
	cur = l->head_node(l);
	while (cur) {
		edge  = cur->data;
		node  = edge->node;
		g->print_data(node->id);
		printf(" ");
		cur = l->next_node(l, cur);
		if (cur == end) {
			break;
		}
	}
	printf("}");
}

/*! @brief  
 *  Print Graph info
 *  @param d	 - Pointer instance of graph
 *  @return 	 - NA
 */
void graph_print(t_gen d)
{
	t_graph *g = (t_graph*)d;
	int i;
	
	printf("%s: vertex:%d edges:%d\n", g->name, g->count, g->total_edges);

	for (i = 0; i < g->count; i++) {
		g->print_data(g->nodes[i].id);
		printf(":");
		graph_neigh_print(g,g->nodes[i].neigh);
		printf("\n");
	} 
}

/*! @brief  
 *  Util function to Print neighbor list of a vetex(node) with edge weights
 *  @param d	 - Pointer instance of graph
 *  @param neigh - Pointer to neigh link list 
 *  @return 	 - NA
 */
void graph_wneigh_print(t_gen d, t_gen neigh)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_gedge *edge;
	t_linklist *l = (t_linklist*)neigh;
	t_llnode *cur, *end;

	printf("{ ");
	cur = l->head_node(l);
	while (cur) {
		edge  = cur->data;
		node  = edge->node;
		printf("<");
		g->print_data(node->id);
		printf(" %d> ", edge->weight);
		cur = l->next_node(l, cur);
		if (cur == end) {
			break;
		}
	}
	printf("}");
}


/*! @brief  
 *  Print Graph info with edge weights
 *  @param d	 - Pointer instance of graph
 *  @return 	 - NA
 */
void graph_wprint(t_gen d)
{
	t_graph *g = (t_graph*)d;
	int i;
	
	printf("%s: vertex:%d edges:%d\n", g->name, g->count, g->total_edges);

	for (i = 0; i < g->count; i++) {
		g->print_data(g->nodes[i].id);
		printf(":");
		graph_wneigh_print(g,g->nodes[i].neigh);
		printf("\n");
	} 
}

/*! @brief  
 *  Utils function used for comparing two different graph edges
 *  @param x	 - Pointer to edge1
 *  @param y	 - Pointer to edge2
 *  @return 	 - Comparision resutlt @see e_cmpr
 */
e_cmpr graph_wedge_cmpr(t_gen x, t_gen y)
{
	t_gedge *A = (t_gedge*)x;
	t_gedge *B = (t_gedge*)y;
	e_cmpr ret = eEQUAL;
	
	if (A->weight > B->weight) {
		ret = eGREAT;
	}
	else if (A->weight < B->weight) {
		ret = eLESS;
	}
	
	return ret;
}

/*! @brief  
 *  Utils function used by genric heap for comparing 
 *  graph edge weights
 *  @param d	 - Pointer to array heap
 *  @param i	 - index 1
 *  @param j	 - index 2
 *  @return 	 - Comparision resutlt @see e_cmpr
 */
e_cmpr graph_wedge_cmpr_idx(t_gen x, int i, int j)
{
	t_gen *arr = (t_gen*)x;
	return graph_wedge_cmpr(arr[i], arr[j]);
}

/*! @brief  
 *  Utils function used by quick sort for comparing 
 *  graph edge weights
 *  @param d	 - Pointer to array 
 *  @param i	 - index 1
 *  @param j	 - index 2
 *  @return 	 - Comparision resutlt @see e_cmpr
 */
e_cmpr graph_wedge_cmpr_idx2(t_gen x, int i, int j)
{
	t_distinfo *arr = (t_distinfo*)x;
	return graph_wedge_cmpr(&arr[i], &arr[j]);
}

/*! @brief  
 *  Utils function used by quick sort for swapping
 *  graph edges
 *  @param d	 - Pointer to array 
 *  @param i	 - index 1
 *  @param j	 - index 2
 *  @return 	 - NA
 */
SWP_IDX(t_distinfo, graph_wedge_swap_idx)

/*! @brief  
 *  Find the shortest path from a given source vertex
 *  to all source nodes in a graph using Dijkstra's algo
 *  @see https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 *  Note: Dijktra's works for graph with no negative edges
 *  @param d	 - Pointer instance of graph
 *  @param data  - Pointer to source vertex data
 *  @return 	 - Pointer to dist array to all nodes in graph
 */
t_gen dijkstra(t_gen d, t_gen data)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_gedge *v, *u;
	t_llnode *cur, *end;
	t_linklist *neigh_list;
	t_distinfo *dist, *tmp;
	t_heap *h;
	t_dparams dp;
	t_gen *pq;
	int alt_weight;

	// Get vertex
	node = g->find(g, data);
	if (node == NULL) {
		return NULL;
	}	

	// Data specific operation for generic min heap
	init_data_params(&dp, eUSER);
	dp.free     = dummy_free;
	dp.cmpr	    = graph_wedge_cmpr; 
	dp.cmpr_idx = graph_wedge_cmpr_idx;
	dp.swap_idx = gen_swp_idx;
	dp.copy_idx = gen_cpy_idx;
	dp.get_idx  = gen_get_idx;

	// Creating a generic min heap to store edges
	pq   = get_mem(g->count, sizeof(t_gen)); 	
	h    = create_heap("Dijkstra's Heap", pq, g->count, eMIN_HEAP, &dp);
	
	// Initalize all dist to all nodes as infinite 
	dist = get_mem(g->count, sizeof(t_distinfo)); 	
	for (int i = 0; i < g->count; i++) {
		dist[i].edge.node   = &g->nodes[i];
		dist[i].edge.weight = INT_MAX; 
		dist[i].parent 	    = NULL;
	}
	
	// Set the source node dist as 0
	dist[node->idx].edge.weight = 0; 
	
	// Add source vertex to heap 
	h->insert(h, &dist[node->idx].edge);
	while (h->empty(h) != true) {
		// Get min dist vertex from heap and traverse all its edges
		// check if dist from cur vertex to its neigh vertex is smaller
		// Using heaps cos extract min is O(1)
		u = h->extract(h);

		neigh_list = (t_linklist*)u->node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			v = (t_gedge*)cur->data;

			// If cur dist is greater than the alt dist
			alt_weight = u->weight + v->weight;
			if (dist[v->node->idx].edge.weight > alt_weight) {
				// Set cur dist as alt dist, update parent
				// and add edge to heap
				dist[v->node->idx].edge.weight = alt_weight;
				dist[v->node->idx].parent = u->node;
				h->insert(h, &dist[v->node->idx].edge);
			}
			
			// Exit after neigh list traversal complete
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	
	// Destroy heap and destroy the array used for storing heap
	h->destroy(h);
	free_mem(pq);

	return dist;
}

/*! @brief  
 *  Find the shortest path from a given source vertex
 *  to all source nodes in a graph with negative edges
 *  this is an improvent of bellman ford using
 *  Shortest Path Faster Algorithm (SPFA)
 *  @see https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm
 *  @param d	 - Pointer instance of graph
 *  @param data  - Pointer to source vertex data
 *  @return 	 - Pointer to dist array to all nodes in graph
 */
t_gen bellman_ford(t_gen d, t_gen data)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_gedge *v, *u;
	t_llnode *cur, *end;
	t_linklist *neigh_list;
	t_distinfo *dist, *tmp;
	t_dparams dp;
	t_queue *q;
	int alt_weight;
	bool *in_q;

	// Get vertex
	node = g->find(g, data);
	if (node == NULL) {
		return NULL;
	}

	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	q = create_queue("bellman_q", g->count, eLL_QUEUE_CIRC, &dp);
	
	// Initalize all dist to all nodes as infinite 
	dist = get_mem(g->count, sizeof(t_distinfo)); 	
	in_q = get_mem(g->count, sizeof(bool)); 	
	for (int i = 0; i < g->count; i++) {
		dist[i].edge.node   = &g->nodes[i];
		dist[i].edge.weight = INT_MAX; 
		dist[i].parent 	    = NULL;
		in_q[i] = false;
	}
	
	// Set the source node dist as 0
	dist[node->idx].edge.weight = 0; 
	q->enq(q, &dist[node->idx].edge);
	in_q[node->idx] = true;
	while (q->empty(q) != true) {
		u = q->deq(q);
		in_q[u->node->idx] = false;
		neigh_list = (t_linklist*)u->node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
	
		while (cur) {
			v = (t_gedge*)cur->data;

			// If cur dist is greater than the alt dist
			alt_weight = dist[u->node->idx].edge.weight + v->weight;
			if (dist[v->node->idx].edge.weight > alt_weight) {
				// Set cur dist as alt dist, update parent
				// and add edge to queue if vertex not already in queue
				dist[v->node->idx].edge.weight = alt_weight;
				dist[v->node->idx].parent = u->node;
				if (in_q[v->node->idx] != true) {
					q->enq(q, &dist[v->node->idx].edge);
					in_q[v->node->idx] = true;
				}

			}

			// Exit after neigh list traversal complete
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	
	q->destroy(q);
	free_mem(in_q);

	return dist;
}

/*! @brief  
 *  Find the Minimum Spanning for weighted undirected graph
 *  Using Prim's Algorithm
 *  @see https://en.wikipedia.org/wiki/Prim%27s_algorithm
 *  @param d	 - Pointer instance of graph
 *  @return 	 - Pointer to dist array to all nodes in graph
 */
t_gen prims_mst(t_gen d)
{
	t_graph *g = (t_graph*)d;
	t_gedge *v, *u;
	t_llnode *cur, *end;
	t_linklist *neigh_list;
	t_distinfo *dist, *tmp;
	t_heap *h;
	t_dparams dp;
	t_gen *pq;

	// Data specific operation for generic min heap
	init_data_params(&dp, eUSER);
	dp.free     = dummy_free;
	dp.cmpr	    = graph_wedge_cmpr; 
	dp.cmpr_idx = graph_wedge_cmpr_idx;
	dp.swap_idx = gen_swp_idx;
	dp.copy_idx = gen_cpy_idx;
	dp.get_idx  = gen_get_idx;

	// Creating a generic min heap to store edges
	pq   = get_mem(g->count, sizeof(t_gen)); 	
	h    = create_heap("Dijkstra's Heap", pq, g->count, eMIN_HEAP, &dp);
	
	// Initalize all dist to all nodes as infinite 
	dist = get_mem(g->count, sizeof(t_distinfo)); 	
	for (int i = 0; i < g->count; i++) {
		dist[i].edge.node   = &g->nodes[i];
		dist[i].edge.weight = INT_MAX; 
		dist[i].parent 	    = NULL;
	}
	
	
	// Set 0 as start vertex
	h->insert(h, &dist[0].edge);
	while (h->empty(h) != true) {
		// Of the edges that connect the tree to vertices not yet in the tree,
		// Find the minimum-weight edge, and transfer it to the tree
		u = h->extract(h);

		neigh_list = (t_linklist*)u->node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			v = (t_gedge*)cur->data;
			
			// If cur edge weight is greater than new edge
			// and the end vertex is not visited
			if (dist[v->node->idx].edge.weight > v->weight) {
				// Set new edge as part of MST, update parent
				// and add edge to heap
				dist[v->node->idx].edge.weight = v->weight;
				dist[v->node->idx].parent = u->node;
				h->insert(h, &dist[v->node->idx].edge);
			}
			
			// Exit after neigh list traversal complete
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	
	// Destroy heap and destroy the array used for storing heap
	h->destroy(h);
	free_mem(pq);

	return dist;
}

/*! @brief  
 *  Find the Minimum Spanning for weighted undirected graph
 *  Using Kruskal's Algorithm
 *  @see https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
 *  @param d	 - Pointer instance of graph
 *  @return 	 - Pointer to dist array to all nodes in graph
 */
t_gen kruskals_mst(t_gen d)
{
	t_graph *g = (t_graph*)d;
	t_gnode *v, *u;
	t_llnode *cur, *end;
	t_linklist *neigh_list;
	t_distinfo *dist, *tmp;
	t_dparams dp;
	t_disjset *set;
	int i, j;

	// Allocate mem for edge list
	tmp  = get_mem(g->total_edges, sizeof(t_distinfo));
	// Allocate mem for storing MST
	dist = get_mem(g->count, sizeof(t_distinfo));
	// Create a disjoint set
	set  = create_disjoint_set("Kruskal graph set", g->total_edges);

	// Create edge list from Adjancency list
	for (j = i = 0; i < g->count; i++) {
		neigh_list = (t_linklist*)(g->nodes[i].neigh);
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			tmp[j].parent = &g->nodes[i];
			tmp[j++].edge = *((t_gedge*)cur->data);
			
			// Exit after neigh list traversal complete
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}

	// Data specific operation for sorting edges
	init_data_params(&dp, eUSER);
	dp.cmpr_idx = graph_wedge_cmpr_idx2;
	dp.swap_idx = graph_wedge_swap_idx;
	
	// Sort the edge List based on weights
	quick_sort(tmp, g->total_edges, &dp);

	// Make a disjoint set for all the vertex in graph
	//(create a forest (a set of trees), where each vertex in the graph is a separate tree)
	set->make(set);

	// Get edges in ascending order from the edge list
	// Kruskals algorithm terminates if MST is formed(dist contains V-1 edges) 
	// or, all edges have been visited
	for (j = i = 0; (j < g->count) && (i < g->total_edges); i++) {
		u = tmp[i].parent;
		v = tmp[i].edge.node;
		
		// If edges connect two different trees add to forest(Minimum spanning Tree)
		if (set->find(set, u->idx) != set->find(set, v->idx)) {
			dist[j++] = tmp[i];
			set->merge(set, u->idx, v->idx);
		}
	}
	
	// Destroy disjoint set and the  edge list
	set->destroy(set);
	free_mem(tmp);

	return dist;
}

/*! @brief  
 *  Destroy instance of graph
 *  @param d	 - Pointer instance of graph
 *  @return 	 - NA
 */
void graph_destroy(t_gen d)
{
	t_graph *g = (t_graph*)d;
	int i;
	
	// Go through each node and delete neigh list and data
	for (i = 0; i < g->count; i++) {
		g->nodes[i].neigh->destroy(g->nodes[i].neigh);
		g->free(g->nodes[i].id, __FILE__, __LINE__);
	}
	
	free_mem(g->nodes);
	free_mem(g);
}


