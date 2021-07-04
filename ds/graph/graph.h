#pragma once
#include "common.h"
#include "link_list.h"

/// graph node
typedef struct gnode {
	int idx;
	t_gen id;
	t_linklist *neigh;
} t_gnode;

/// Level and Parent info after BFS walk
typedef struct bfs_info{
	int level;
	t_gen parent;	
} t_bfsinfo;

/// graph struct defn
typedef struct graph {
	// graph info params
	char *name;
	int count;
	int max_size;
	e_data_types dtype;

	// graph nodes
	t_gnode *nodes;

	// graph routines
	f_gen2 add_vertex;
	f_gen2 del_vertex;
	f_gen3 add_edge;
	f_gen3 del_edge;
	f_gen3 add_edge_sym;
	f_gen3 del_edge_sym;
	f_gen3 has_edge;
	f_gen2 bfs;
	f_gen2 dfs;
	f_find find;
	f_len len;
	f_print print;
	f_destroy destroy;
	
	// routies for operating on data
	f_cmpr cmpr;
	f_swap swap;
	f_free free;
	f_print print_data;
} t_graph;

/// graph interface APIs
t_gen create_graph(char *name, int size, t_dparams *prm);
