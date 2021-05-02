#include "common.h"
#include "link_list.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"

int main(int argc, char *argv[])
{
	int i ;	

	mem_init();
	logger_init();
	fault_manager_init(NULL);

#if 1
	char c,*cp,*sp,str[][64] = {"I", "See", "Everyting"};
	float f,*fp;
	int *ip;

	LOG_INFO("COMMON", "------ LINK LIST TEST -----\n");		
	t_gen l1 = create_link_list("INT DLL",eDOUBLE_LINKLIST, eINT32);
	t_gen l2 = create_link_list("CHAR SLL",eSINGLE_LINKLIST, eINT8);
	t_gen l3 = create_link_list("FLOAT SCLL",eSINGLE_CIRCULAR_LINKLIST, eFLOAT);
	t_gen l4 = create_link_list("STRING DCLL",eDOUBLE_CIRCULAR_LINKLIST, eSTRING);
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		((t_linklist*)l2)->add(l2, assign_char(c));

		((t_linklist*)l1)->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		((t_linklist*)l3)->add(l3, assign_float(f));

		((t_linklist*)l4)->add(l4, assign_string(str[i]));
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
	LOG_INFO("TEST", "deleting nodes in link list\n");
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		cp = ((t_linklist*)l2)->del(l2, &c);
		free_mem(cp);

		ip = ((t_linklist*)l1)->del(l1, &i);
		free_mem(ip);

		f= (float)i+0.222 / 2.0f;
		fp = ((t_linklist*)l3)->del(l3, &f);
		free_mem(fp);

		sp = ((t_linklist*)l3)->del(l4, &str[i]);
		free_mem(sp);
	}

	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		((t_linklist*)l2)->append(l2, assign_char(c));

		((t_linklist*)l1)->append(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		((t_linklist*)l3)->append(l3, assign_float(f));

		((t_linklist*)l4)->append(l4, assign_string(str[i]));
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
	destroy_link_list(l1);
	destroy_link_list(l2);
	destroy_link_list(l3);
	destroy_link_list(l4);

	LOG_INFO("COMMON", "------ STACK TEST -----\n");		
	t_gen s1 = create_stack("Up Stack", 10, eARRAY_STACK, eINT32);
	t_gen s2 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, eINT8);
	t_gen s3 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, eFLOAT);
	for(i = 0; i < 10; i++) {
		((t_stack*)s1)->push(s1, assign_int(i));
		c= 'c' + i;
		((t_stack*)s2)->push(s2, assign_char(c));
		f= (float)i+0.222 / 2.0f;
		((t_stack*)s3)->push(s3, assign_float(f));
	}
	print_stack(s1);
	print_stack(s2);
	print_stack(s3);
	for(i = 0; i < 4; i++) {
		ip = ((t_stack*)s1)->pop(s1);
		free_mem(ip);
		cp = ((t_stack*)s2)->pop(s2);
		free_mem(cp);
		fp = ((t_stack*)s3)->pop(s3);
		free_mem(fp);
	}
	print_stack(s1);
	print_stack(s2);
	print_stack(s3);
	for(i = 4; i > 0; i--) {
		((t_stack*)s1)->push(s1, assign_int(i));
		c= 'c' + i;
		((t_stack*)s2)->push(s2, assign_int(c));
		f= (float)i+0.222 / 2.0f;
		((t_stack*)s3)->push(s3, assign_float(f));
	}
	print_stack(s1);
	print_stack(s2);
	print_stack(s3);
	destroy_stack(s1);
	destroy_stack(s2);
	destroy_stack(s3);

	t_gen q1 = create_queue("Queue1", 10, eARRAY_QUEUE_CIRC, eINT8);
	t_gen q2 = create_queue("Queue2", 10, eARRAY_QUEUE_CIRC, eFLOAT);

	LOG_INFO("COMMON", "------ QUEUE TEST -----\n");		

	for(i = 0; i < 10; i++) {
		c= 'c' + i;
		((t_queue*)q1)->enq(q1, assign_char(c));
		f= (float)i+0.222 / 2.0f;
		((t_queue*)q2)->enq(q2, assign_float(f));
	}
	print_queue(q1);
	print_queue(q2);
	for(i = 0; i < 10; i++) {
		cp = ((t_queue*)q1)->deq(q1);
		free_mem(cp);
	}
	print_queue(q1);
	print_queue(q2);
	for(i = 0; i < 4; i++) {
		c= 'c' + i;
		((t_queue*)q1)->enq(q1, assign_char(c));
	}
	print_queue(q1);
	print_queue(q2);
	destroy_queue(q1);
	destroy_queue(q2);
#endif
	LOG_INFO("COMMON", "------ HEAP TEST -----\n");		
	float arr1[10]={0};
	int arr[10] = {1,53,32,43,3,23,11,209};
	char carr[10] = {'&', '^', 'j', 'a', 'r', 'e', 'm', '*', '%', '!'};
	t_gen h1 = create_heap("INT HEAP", arr,10, eMIN_HEAP, eINT32);
	t_gen h2 = create_heap("CHAR HEAP", carr,10, eMAX_HEAP, eINT8);
	t_gen h3 = create_heap("float HEAP", arr1,10, eMIN_HEAP, eFLOAT);
	
	// Insert element
	 f = -1.2234f;
	((t_heap*)h3)->insert(h3,&f);
	 f = -10.3242f;
	((t_heap*)h3)->insert(h3,&f);
	 f = 1000.2f;
	((t_heap*)h3)->insert(h3,&f);
	
	printf("Sorting\n");
	// heap sort data;
	((t_heap*)h1)->sort(h1);
	((t_heap*)h2)->sort(h2);

	print_heap(h1);
	print_heap(h2);
	print_heap(h3);

	// heapify array
	((t_heap*)h1)->build(h1);
	((t_heap*)h2)->build(h2);
	printf("Heapify'd array\n");
	printf("%f\n", *(float*)(((t_heap*)h3)->del(h3)));
	printf("%f\n", *(float*)(((t_heap*)h3)->del(h3)));
	print_heap(h1);
	print_heap(h2);
	print_heap(h3);

	destroy_heap(h1);
	destroy_heap(h2);
	destroy_heap(h3);

	mem_finit();

	return 0;

}
