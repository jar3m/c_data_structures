## C Everything
* This is a C repository containing a curated set of data structures and algorithm.
* The data structures are implemented keeping them Generic and Abstract.
* Genericness: Since in C any data structure is completely type dependent, we've tried to achieve a genric data structure that supports any standard data types (int, char, float, etc..) and user defined data types (struct user {})
    - The means by which we achieved a data structure by storing the pointer to the data (std or user defined) rather the data itself
    - Given below is a snippet of code explaining the same,
``` markdown
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

* Link List
  * Singly linked list
  * Doubly linked list 
  * Circular linked list 
  * Doubly Circular linked list 
  * XOR linked list 

* Stacks
  * Array based 
  * Link List based

* Queues
  * Array based 
  * Link List based

* Hashes

* Disjoint Sets

* Heaps (Array based Binary heap)
  * Min heap
  * Max heap

* Trees
  * Binary Search Tree
  * AVL Trees 

* Graphs
 * Weighted/Unweighted
 * Symmetric/Assymetric

# ALGORITHMS
* Searching
  * Linear Search
  * Binary Search

* Sorting
  * Insertion Sort
  * Selection Sort
  * Bubble Sort
  * Quick Sort
  * Merge Sort
  * Heap Sort

* Graph Algorithms
  * Dijkstra's Shortest Path
  * Bellman Ford Shortest Path 
  * Prim's Minimum Spanning Tree
  * Kruskal's Minimus Spanning Tree



# BUILD
$ make clean; make all

# RUN
$ ./foo.out
