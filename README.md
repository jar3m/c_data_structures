
# **Title: [C Everything](https://jar3m.github.io/c_everything/)**

# INFO

* This is a C repository containing a curated set of data structures and algorithm.[website](https://jar3m.github.io/c_everything)
* The data structures are implemented keeping them Generic and Abstract.
* Genericness: Since in C any data structure is completely type dependent, we've tried to achieve a genric data structure that supports any standard data types (int, char, float, etc..) and user defined data types (struct user {})
    - The means by which we achieved a data structure by storing the pointer to the data (std or user defined) rather the data itself
    - Given below is a snippet of code explaining the same,
```markdown
// Link list node definition
typdef void* t_gen;                     //< Generic data pointer

typedef struct llnode {
        t_gen data;                     //< Pointer to the data to be stored in link list
        struct llnode *nxt;             //< Pointer to next node in list
        struct llnode *prv;             //< Pointer to prev node in list
} t_llnode;

```
* Abstractness: The operations/procedures for each data structure is abstracted to the user by using function pointers, thus creating a psuedo class like structure
```markdown
t_linklist *l;
t_dparams dp;

// Data type specific operations to be given to data structure
init_data_params(&dp, eSTRING);

// Create a string XOR link list
l = create_link_list("STRING XORLL",eXOR_LINKLIST, &dp);


// Add elements to linklist
l->add(l, "Hello");
l->add(l, "World");

// print linklist
l->print(l);

// Destroy linklist
l->destroy(l);
```


# LIST OF DATA STRUCTURES

* [**Link List**](https://github.com/jar3m/c_everything/blob/master/ds/link_list/link_list.c)
  * Singly linked list
  * Doubly linked list 
  * Circular linked list 
  * Doubly Circular linked list 
  * XOR linked list 

* [**Stacks**](https://github.com/jar3m/c_everything/blob/master/ds/stack/stack.c) 
  * Array based 
  * Link List based

* [**Queues**](https://github.com/jar3m/c_everything/blob/master/ds/queue/queue.c) 
  * Array based 
  * Link List based

* Hashes

* [Disjoint Sets](https://github.com/jar3m/c_everything/blob/master/ds/disjoint_set/disjoint_set.c) 

* [Heaps (Array based Binary heap)](https://github.com/jar3m/c_everything/blob/master/ds/heap/heap.c)
  * Min heap
  * Max heap

* [Trees](https://github.com/jar3m/c_everything/blob/master/ds/tree/tree.c) 
  * Binary Search Tree
  * AVL Trees 

* [Graphs](https://github.com/jar3m/c_everything/blob/master/ds/graph/graph.c)
  * Weighted/Unweighted
  * Symmetric/Assymetric

# ALGORITHMS
* [Searching](https://github.com/jar3m/c_everything/blob/master/ds/array/array.c)
  * Linear Search
  * Binary Search

* [Sorting](https://github.com/jar3m/c_everything/blob/master/ds/array/array.c) 
  * Insertion Sort
  * Selection Sort
  * Bubble Sort
  * Quick Sort
  * Merge Sort
  * Heap Sort

* [Graph Algorithms](https://github.com/jar3m/c_everything/blob/master/ds/graph/graph.c)
  * Dijkstra's Shortest Path
  * Bellman Ford Shortest Path 
  * Prim's Minimum Spanning Tree
  * Kruskal's Minimus Spanning Tree

# Code Documentation
* [*Source code Documentation*](https://jar3m.github.io/c_everything/docs/html/index.html)
* [*File List*](https://jar3m.github.io/c_everything/docs/html/files.html)
* [*Generic Data*](https://jar3m.github.io/c_everything/docs/html/generic__def_8h.html)
* [*Link List docs*](https://jar3m.github.io/c_everything/docs/html/link_list_8c.html)
* [*Stack docs*](https://jar3m.github.io/c_everything/docs/html/stackt_8c.html)
* [*Queue docs*](https://jar3m.github.io/c_everything/docs/html/queue_8c.html)
* [*Heap docs*](https://jar3m.github.io/c_everything/docs/html/heap_8c.html)
* [*Searching Sorting docs*](https://jar3m.github.io/c_everything/docs/html/array_8c.html)
* [*Tree docs*](https://jar3m.github.io/c_everything/docs/html/tree_8c.html)
* [*Disjoint Sets docs*](https://jar3m.github.io/c_everything/docs/html/disjoint_set_8c.html)
* [*Graph docs*](https://jar3m.github.io/c_everything/docs/html/graph_8c.html)

# CONFIGURE
Def.make change flags

# BUILD
$ make clean; make all

# TEST
Test case are as defined in test/src/test.c

# RUN
$ ./foo.out
