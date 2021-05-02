#include "queue.h"

bool queue_full(t_gen d);
bool queue_empty(t_gen d);
int queue_size(t_gen d);

t_gen queue_enqueue_ll(t_gen s, t_gen data);
t_gen queue_dequeue_ll(t_gen s);
t_gen queue_enqueue_arr(t_gen s, t_gen data);
t_gen queue_dequeue_arr(t_gen s);

f_enq q_enq[] = {queue_enqueue_ll, queue_enqueue_arr};
f_deq q_deq[] = {queue_dequeue_ll, queue_dequeue_arr};
/*! \brief Brief description.
 *  Destroy queue instance 
*/
t_gen create_queue (char *name, int max_size, e_queuetype qtype, e_data_types dtype)
{
	t_queue *q = get_mem(1, sizeof(t_queue));
	
	// Init queue variables
	q->name = name;
	q->max_size = max_size;
	q->type = qtype;
	q->count = 0;
	
	// Bind queue routines
	q->full = queue_full;
	q->empty = queue_empty;
	q->len = queue_size;
	q->print = print_queue;
	q->free = FREE_MEM;
	
	
	q->enq = q_enq[qtype];
	q->deq = q_deq[qtype];
	q->front = q->rear = -1;
	// create queue space
	switch (qtype) 
	{
		case eARRAY_QUEUE_CIRC:
			q->data = get_mem(max_size, sizeof(t_gen));
		break;
		case eLL_QUEUE_CIRC:
			q->data = create_link_list("queue_data", 
					eDOUBLE_LINKLIST, dtype);
		break;
	}

	switch(dtype)
	{
		case eINT8:
			//char list;
			q->print_data = print_char;
			break;
		case eINT32:
			//int list;
			q->print_data = print_int;
			break;
		case eFLOAT:
			//float list;
			q->print_data = print_float;
			break;
		case eSTRING:
			//string list;
			q->print_data = print_str;
			break;
	}

	return (t_gen)q;
}

/*! \brief Brief description.
 *  Destroy queue instance 
*/
void destroy_queue (t_gen s)
{
	t_queue *q = (t_queue*)s;
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
			destroy_link_list(q->data);
		break;
	}

	// Free queue
	free_mem(q);
}

/*! \brief Brief description.
 *  add element in queue
*/
t_gen queue_enqueue_arr(t_gen s, t_gen data)
{
	t_queue *q = (t_queue*)s;

	// return if queue full
	if (q->full(q) == true) {
		LOG_WARN("QUEUES", "%s: Queue Full\n",q->name);
		return NULL;
	}

	// queue empty (added first element)
	q->front  = (q->front != -1) ? q->front : 0;

	// Incr Rear and add data to queue
	q->rear = (q->rear + 1) % q->max_size;
	q->data[q->rear] = data;
	q->count++;
	
	return data;
}

/*! \brief Brief description.
 *  pop front element in queue
*/
t_gen queue_dequeue_arr(t_gen s)
{
	t_queue *q = (t_queue*)s;
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
		q->front =  (q->front + 1) % q->max_size;
	}

	return data;

}

/*! \brief Brief description.
 *  add element in queue
*/
t_gen queue_enqueue_ll(t_gen s, t_gen data)
{
}

/*! \brief Brief description.
 *  pop front element in queue
*/
t_gen queue_dequeue_ll(t_gen s)
{
}

/*! \brief Brief description.
 *  Check queue full 
*/
bool queue_full(t_gen d)
{
	return ((t_queue*)d)->count >= ((t_queue*)d)->max_size;
}

/*! \brief Brief description.
 *  Check queue empty 
*/
bool queue_empty(t_gen d)
{
	return ((t_queue*)d)->count == 0;
}

/*! \brief Brief description.
 *  Return queue size
*/
int queue_size(t_gen d)
{
	return ((t_queue*)d)->count;
}

/*! \brief Brief description.
 *  print_queue_info
*/
void print_queue(t_gen d)
{
	t_queue *q = (t_queue*)d; 
	int i;

	printf("%s {max: %d} {size: %d} {front/rear: [%d:%d]} \n[",q->name,
			q->max_size, q->count, q->front,q->rear);
	for (i = q->front; (i != -1) && (i <= q->rear); i ++) {
	//	printf("%d ",*(int*)(q->data[i]));
		q->print_data(q->data[i]);
		printf(", ");
	}
	printf("]\n");
}
