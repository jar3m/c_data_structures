/*! @file graph.c
    @brief 
    Contains definitions of routines supported by graph
*/
#include "graph.h"
#include "link_list.h"
#include "queue.h"
#include "stack.h"

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
t_gen graph_bfs(t_gen d, t_gen n);
t_gen graph_dfs(t_gen d, t_gen n);
void graph_toplogicaly_order_dag(t_gen d);
void graph_neigh_print(t_gen d, t_gen neigh);
void graph_print(t_gen d);
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
	g->bfs	          = graph_bfs;
	g->dfs	          = graph_dfs;
	g->topo_order_dag = graph_toplogicaly_order_dag;
	g->find 	  = graph_find;
	g->len	 	  = graph_len;
	g->print 	  = graph_print;
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
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
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
 *  @param d	- Pointer instance of graph
 *  @param n1	- Pointer to data1
 *  @param n2	- Pointer to data2
 *  @return 	- Pointer to Vertex(node) else null
 */
t_gen graph_add_edge(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gnode *A, *B;

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
	// link N1->N2
	A->neigh->append(A->neigh, B);

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
	A->neigh->del(A->neigh, B);
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
		node->neigh->del(node->neigh, A);
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
			neigh = cur->data;
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
			neigh = cur->data;
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
			neigh = cur->data;
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
				n = neigh_list->del_idx(neigh_list, 0);
				neigh_list->append(neigh_list, n);
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
 *  The topologicaly order nodes instead of being printed
 *  can be pushed to link list and return
 *  @param d	 - Pointer instance of graph
 *  @return 	 - NA
 */
void graph_toplogicaly_order_dag(t_gen d)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node;
	t_linklist *neigh_list;
	t_llnode *cur,*end;
	int *indegree, i;
	t_dparams dp;
	t_queue *q;

	// Create queue and array for indegree
	indegree = get_mem(g->count, sizeof(int));
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	q = create_queue("topo_dag", g->count, eLL_QUEUE_CIRC, &dp);
	
	// Indegree initialization
	for (i = 0; i < g->count; i++) {
		indegree[i] = 0;
	}

	// Update indegree for all nodes
	for (i = 0; i < g->count; i++) {
		neigh_list = g->nodes[i].neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			node = cur->data;
			indegree[node->idx] += 1;
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	
	// Add vertices with indegree 0
	for (i = 0; i < g->count; i++) {
		if (indegree[i] == 0) {
			q->enq(q, &g->nodes[i]);
		}
	}
	
	// Start exploration to sort/order by
	// Enumerating the vertices(delete/visited)
	printf("Topologicaly order nodes: [ ");
	while (q->empty(q) != true) {
		node = q->deq(q);
		g->print_data(node->id);
		printf(" ");
		// Enumerate node, i.e, mark as visited
		indegree[node->idx] = -1;
		
		// update indegree of neighbors
		neigh_list = node->neigh;
		cur = neigh_list->head_node(neigh_list);
		end = neigh_list->end_node(neigh_list);
		while (cur) {
			node = cur->data;
			indegree[node->idx] -= 1;
			
			// neigh node indegree is 0 push to queue 
			if (indegree[node->idx] == 0) {
				q->enq(q, node);
			}	
			// Get next neigh
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	printf(" ]\n");
	
	q->destroy(q);
	free_mem(indegree);
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
	t_linklist *l = (t_linklist*)neigh;
	t_llnode *cur, *end;

	printf("{ ");
	cur = l->head_node(l);
	while (cur) {
		node = (t_gnode*)cur->data;
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


