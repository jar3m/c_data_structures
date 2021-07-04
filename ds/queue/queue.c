/*! @file queue.c
    @brief 
    Contains definitions of routines supported by queue 
*/

#include "queue.h"


void queue_enqueue_ll(t_gen s, t_gen data);
t_gen queue_dequeue_ll(t_gen s);

void queue_enqueue_arr(t_gen s, t_gen data);
t_gen queue_dequeue_arr(t_gen s);

t_gen queue_peek(t_gen d, int idx);
bool queue_full(t_gen d);
bool queue_empty(t_gen d);
int queue_size(t_gen d);
void queue_print(t_gen d);
void destroy_queue (t_gen d);

/// Look Up function ptrs to enq elems to queue
f_ins q_enq[] = {queue_enqueue_ll, queue_enqueue_arr};

/// Look Up function ptrs to deq elems to queue
f_gen q_deq[] = {queue_dequeue_ll, queue_dequeue_arr};


/*! @brief  
 *  Destroy queue instance 
 *  @param name     - Name of queue instance
 *  @param max_size - Max size of queue instance
 *  @param type     - Type of queue to be created
 *  @param prm      - Data type specific parameters
 *  @return         - Pointer to instance of queue
*/
t_gen create_queue (char *name, int max_size, e_queuetype qtype, t_dparams *prm)
{
	t_queue *q = get_mem(1, sizeof(t_queue));
	
	// Init queue variables
	q->name 	= name;
	q->max_size	= max_size;
	q->type 	= qtype;
	q->count	= 0;
	q->front 	= q->rear = -1;
	
	// Bind queue routines
	q->full	 	= queue_full;
	q->empty	= queue_empty;
	q->len 		= queue_size;
	q->print 	= queue_print;
	q->enq 		= q_enq[qtype];
	q->deq 		= q_deq[qtype];
	q->peek 	= queue_peek;
	q->destroy	= destroy_queue;

	// create queue space depending on link list or array based
	switch (qtype) 
	{
		case eARRAY_QUEUE_CIRC:
			q->data = get_mem(max_size, sizeof(t_gen));
		break;
		case eLL_QUEUE_CIRC:
			q->data = create_link_list("queue_data", 
					eDOUBLE_LINKLIST, prm);
		break;
	}
	q->print_data	= prm->print_data;
	q->free 	= prm->free;

	return (t_gen)q;
}


/*! @brief  
 *  add element in queue
 *  @param d    - Pointer to instance of queue 
 *  @param data - Pointer to the data to be pushed
 *  @return 	- NA
*/
void queue_enqueue_arr(t_gen d, t_gen data)
{
	t_queue *q = (t_queue*)d;

	// return if queue full
	if (q->full(q) == true) {
		LOG_WARN("QUEUES", "%s: Queue Full\n",q->name);
	}

	// queue empty (added first element)
	q->front  = (q->front != -1) ? q->front : 0;

	// Incr Rear and add data to queue
	q->rear = (q->rear + 1) % q->max_size;
	q->data[q->rear] = data;
	q->count++;
	
}

/*! @brief  
 *  pop front element in queue
 *  @param d    - Pointer to instance of queue 
 *  @return 	- Pointer to the data to be poped from
*/
t_gen queue_dequeue_arr(t_gen d)
{
	t_queue *q = (t_queue*)d;
	t_gen data;

	// return if queue empty 
	if (q->empty(q) == true) {
		LOG_WARN("QUEUES", "%s: Queue Empty\n",q->name);
		return NULL;
	}

	// get queue element 
	data = q->data[q->front];
	
	// if last element read reset front and rear of queue to -1
	q->count--;
	if (q->front == q->rear) {
		q->rear = q->front = -1;
	} else {
		q->front = (q->front + 1) % q->max_size;
	}

	return data;

}

/*! @brief  
 *  peek front element in queue
 *  @param d    - Pointer to instance of queue 
 *  @param idx  - Index of data to peek
 *  @return 	- Pointer to the data to data to be peeked
*/
t_gen queue_peek(t_gen d, int idx)
{
	t_queue *q = (t_queue*)d;
	t_gen node;
	t_linklist *l;

	// return if queue empty 
	if (q->empty(q) == true) {
		LOG_WARN("QUEUES", "%s: Queue Empty\n",q->name);
		return NULL;
	}

	// index out of bound
	if ((idx < 0) && (idx >= q->count)) {
		LOG_WARN("QUEUE", "index is out of bounds\n", q->count);
		return NULL;
	}

	// get queue element for array based queue
	if (q->type ==eARRAY_QUEUE_CIRC) {
		return q->data[idx];
	}
	
	// get queue element for linklist based queue
	l = (t_linklist*)q->data;
	node = l->get_idx(l, idx);

	return l->get_node_data(node);
	
}

/*! @brief  
 *  add element in queue
 *  @param d    - Pointer to instance of queue 
 *  @param data - Pointer to the data to be pushed
 *  @return 	- NA
*/
void queue_enqueue_ll(t_gen d, t_gen data)
{
	t_queue *q = (t_queue*)d;
	t_linklist *l = (t_linklist*)q->data;

	// return if queue full
	if (q->full(q) == true) {
		LOG_WARN("QUEUES", "%s: Queue Full\n",q->name);
	}
	
	// Incr Rear and add data to queue
	q->count++;
	l->append(l, data);
}

/*! @brief  
 *  pop front element in queue
 *  @param d    - Pointer to instance of queue 
 *  @return 	- Pointer to the data to be popped from
*/
t_gen queue_dequeue_ll(t_gen d)
{
	t_queue *q = (t_queue*)d;
	t_linklist *l = (t_linklist*)q->data;

	// return if queue full
	if (q->full(q) == true) {
		LOG_WARN("QUEUES", "%s: Queue Full\n",q->name);
	}
	
	// Decr count and pop first node in linklist
	q->count--;

	return l->del_idx(l, 0);
}

/*! @brief  
 *  Check queue full 
 *  @param d    - Pointer to instance of queue 
 *  @return 	- true if full
*/
bool queue_full(t_gen d)
{
	return ((t_queue*)d)->count >= ((t_queue*)d)->max_size;
}

/*! @brief  
 *  Check queue empty 
 *  @param d    - Pointer to instance of queue 
 *  @return 	- true if empty
*/
bool queue_empty(t_gen d)
{
	return ((t_queue*)d)->count == 0;
}

/*! @brief  
 *  Return queue size
 *  @param d    - Pointer to instance of queue 
 *  @return 	- size of queue
*/
int queue_size(t_gen d)
{
	return ((t_queue*)d)->count;
}

/*  @brief
 *  Util function to get type of queue in string
 *  @param type  - Stack Type
 *  @return String of queue type
*/
static char * get_qname(e_queuetype type)
{
	switch(type) {
		case eLL_QUEUE_CIRC:
			return "LL_QUEUE";
		case eARRAY_QUEUE_CIRC:
			return "ARRAY_QUEUE";
	}
	return "UNDEFINED";
}

/*! @brief  
 *  queue_print_info
 *  @param d    - Pointer to instance of queue 
 *  @return 	- NA
*/
void queue_print(t_gen d)
{
	t_queue *q = (t_queue*)d; 
	int i;
	t_linklist *l;

	printf("%s {max: %d} {type:%s} {size: %d} {front/rear: [%d:%d]} \n",q->name,
			q->max_size, get_qname(q->type), q->count, q->front,q->rear);
	switch (q->type) {
		case eARRAY_QUEUE_CIRC:
			printf("[");
			for (i = q->front; (i != -1) && (i <= q->rear); i ++) {
				q->print_data(q->data[i]);
				printf(", ");
			}
			printf("]\n");
		break;
		case eLL_QUEUE_CIRC:
			l = (t_linklist*)q->data;
			l->print(l);
		break;
	}
}

/*! @brief  
 *  Destroy queue instance 
 *  @param d    - Pointer to instance of queue 
 *  @return 	- NA
*/
void destroy_queue (t_gen d)
{
	t_queue *q = (t_queue*)d;
	t_linklist *l;
	int i;

	// Free created queue space
	switch (q->type) 
	{
		case eARRAY_QUEUE_CIRC:
			while (q->empty(q) != true) {
				q->free(q->deq(q), __FILE__, __LINE__);
			}
			free_mem(q->data);
		break;
		case eLL_QUEUE_CIRC:
			l = (t_linklist*)q->data;
			l->destroy(l);
		break;
	}

	// Free queue
	free_mem(q);
}
