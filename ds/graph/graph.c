#include "graph.h"
#include "link_list.h"
#include "queue.h"

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
void graph_print(t_gen d);
void graph_destroy(t_gen d);


t_gen create_graph(char *name, int size, t_dparams *prm)
{
	t_graph *g = get_mem(1, sizeof(t_graph));

	// Initailze graph Params
	g->name = name;
	g->count = 0;
	g->max_size = size;
	g->dtype = prm->type;
	g->nodes = get_mem(size, sizeof(t_gnode));
	
	// Initailze graph routines
	g->add_vertex = graph_add_vertex; 
	g->del_vertex = graph_del_vertex;
	g->add_edge = graph_add_edge; 
	g->del_edge = graph_del_edge;
	g->has_edge = graph_has_edge;
	g->add_edge_sym = graph_add_edge_sym; 
	g->del_edge_sym = graph_del_edge_sym;
	g->bfs = graph_bfs;
	g->dfs = graph_dfs;
	g->find = graph_find;
	g->len = graph_len;
	g->print = graph_print;
	g->destroy = graph_destroy;

	// Initailze datatype based operations req for prop working of graph
	g->cmpr 	= prm->cmpr;
	g->swap 	= prm->swap;
	g->free 	= prm->free;
	g->print_data 	= prm->print_data;

	return (t_gen)g;
}


int graph_len(t_gen g)
{
	return ((t_graph*)g)->count;
}

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
	A->neigh->find(A->neigh, B);
}

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

	// link N1->N2
	A->neigh->add(A->neigh, B);

	return A;
}

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

t_gen graph_del_edge_sym(t_gen d, t_gen n1, t_gen n2)
{
	t_graph *g = (t_graph*)d;
	t_gen ret;

	// unlink N1->N2
	ret = g->del_edge(g, n1, n2);
	
	// unlink N2->N1
	ret = g->del_edge(g, n2, n1);

}

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

t_gen graph_bfs(t_gen d, t_gen n)
{
	t_graph *g = (t_graph*)d;
	t_gnode *node, *neigh;
	t_queue *q;
	t_bfsinfo *bfs = NULL;
	t_dparams dp;
	t_linklist *neigh_list;
	t_llnode *cur, *end;

	// Find node
	node = g->find(g, n);

	// return if node doesn't exist
	if (node == NULL) {
		return bfs;
	}

	// Create queue and bfs info array for bfs 
	init_data_params(&dp, eINT32);
	dp.free = dummy_free;
	q = create_queue("Qdel_tree", g->count, eLL_QUEUE_CIRC, &dp);
	bfs = get_mem(g->count, sizeof(t_bfsinfo));
	
	// Init bfs data struct for vertex exploration
	for (int i = 0; i < g->count; i++) {
		bfs[i].level = -1; bfs[i].parent = NULL;
	}
	
	bfs[node->idx].level = 0; 
	bfs[node->idx].parent = NULL; 
	q->enq(q, node);
	while (q->empty(q) != true) {
		node = q->deq(q);

		// For each vertex in queue
		// Increment level and update parent for each new vertex
		neigh_list = (t_linklist*)node->neigh;
		cur = neigh_list->head_node(neigh_list);
		while (cur) {
			neigh = cur->data;
			// If neigh node not visited add neigh to queue 
			if (bfs[neigh->idx].level == -1) {
				bfs[neigh->idx].level = bfs[node->idx].level + 1;
				bfs[neigh->idx].parent = node->id;
				q->enq(q, neigh);
			}
			// Get next node in neigh list
			cur = neigh_list->next_node(neigh_list, cur);
			if (cur == end) {
				break;
			}
		}
	}
	printf("\n");

	q->destroy(q);
	
	return bfs;
}

t_gen graph_dfs(t_gen d, t_gen n)
{
	return NULL;
}
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

void graph_print(t_gen d)
{
	t_graph *g = (t_graph*)d;
	int i;
	
	printf("%s: len:%d\n", g->name, g->count);

	for (i = 0; i < g->count; i++) {
		g->print_data(g->nodes[i].id);
		printf(":");
		graph_neigh_print(g,g->nodes[i].neigh);
		printf("\n");
	} 
}

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


