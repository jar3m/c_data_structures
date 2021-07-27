/*! @file graph.h
    @brief 
    Contains declations of graph types, operations and structure
*/
#pragma once
#include "common.h"
#include "link_list.h"

/// graph Vertex
typedef struct gnode {
	t_gen id;			///< Pointer to store Data
	int idx;			///< Index of vertex in adaceny list
	t_linklist *neigh;		///< Link List to neighbor vertices(nodes)
} t_gnode;

/// graph neighbor edges represented in neigh list
typedef struct gedge {
	t_gnode *node;			///< Pointer to neighbor vertex
	unsigned int weight;			///< Cost of the edge
} t_gedge;

// fn ptr for adding weighted edge
typedef t_gen (*f_wedge)(t_gen, t_gen, t_gen, int);	

/// graph struct defn
typedef struct graph {
	// graph info params
	char *name;			///< Graph Instance Name
	int count;			///< Vertex Count of graph
	int max_size;			///< Max Vertex count of graph
	int total_edges;		///< Edge count of graph

	// graph nodes
	t_gnode *nodes;			///< Adaceny List Representation of graph vertices

	// graph routines
	f_gen2 add_vertex;		///< routine to add a vertex in graph
	f_gen2 del_vertex;		///< routine to del a vertex in graph
	f_gen3 add_edge;		///< routine to add an edge in graph
	f_gen3 del_edge;		///< routine to del an edge in graph
	f_gen3 add_edge_sym;		///< routine to add a symmetric edge in graph
	f_gen3 del_edge_sym;		///< routine to del a symmetric edge in graph
	f_wedge add_wedge;		///< routine to add a weighted edge in graph
	f_wedge add_wedge_sym;		///< routine to add a weighted symmetric edge in graph
	f_gen3 has_edge;		///< routine to check an edge between two vertices graph
	f_gen2 bfs;			///< routine to Breadth First Search in graph
	f_gen2 dfs;			///< routine to Depth First Search in graph
	f_gen conn_comp;		///< routine to get the connected components in graph
	f_gen topo_order_dag;		///< routine to topologica order a DAG
	f_find find;			///< routine to find a vertex in graph
	f_len len;			///< routine to get vertex count in graph
	f_print print;			///< routine to print graph info
	f_print wprint;			///< routine to print graph info with edge weights
	f_destroy destroy;		///< routine to destroy the graph instance
	
	// routies for operating on data
	f_cmpr cmpr;
	f_swap swap;
	f_free free;
	f_print print_data;
} t_graph;

/// Level and Parent info after BFS walk
typedef struct bfs_info{
	t_gen parent;			///< Pointer to Parent Vertex
	int level;			///< Level of vertex from the source
	int comp;			///< Subgraph id of vertex
} t_bfsinfo;

/// Level and Parent info after DFS walk
typedef struct dfs_info{
	t_gen parent;			///< Pointer to Parent Vertex
	int pre;			///< Pre Interval of a vertex on dfs walk
	int post;			///< Post Interval of a vertex on dfs walk
	int comp;			///< Subgraph id of vertex
	int visited_neighbors;		///< Used internally Flag indicating neighbors still to be visited
} t_dfsinfo;

/// Longest Path and Node order after DAG ordering
typedef struct dag_info{
	t_gen node;			///< Pointer to Vertex in topologically sorted order
	int longest_path;		///< Longest path to vertex in DAG
	int indegree;			///< Used internally for topologicaly order and find longest path in DAG
} t_daginfo;

/// Dist info
typedef struct dist_info {
	t_gedge edge;			///< Pointer to edge
	t_gnode *parent;		///< Pointer to Vertex vertex
} t_distinfo;

/// graph interface APIs
t_gen create_graph(char *name, int size, t_dparams *prm);
t_gen dijkstra(t_gen d, t_gen data);
