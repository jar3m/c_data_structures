#include "common.h"
#include "link_list.h"
#include "stack.h"
#include "queue.h"

int main(int argc, char *argv[])
{
	size_t size = 0;
	int *ptr[100];
	int i ;	

	mem_init();
	logger_init();
	fault_manager_init(NULL);
	for (i = 0; i < 100; i ++) {
		ptr[i] = (int *)get_mem(1, sizeof(int));
		size += sizeof(*(ptr[i]));
	}
	printf("size of allocated memory = %lu\n" , size);
	for (i = 0; i < 100; i++) {
		free_mem(ptr[i]);
	}


	LOG_ERROR("COMMON", "Hello World\n");
	LOG_WARN("COMMON", "Hello World\n");		
	LOG_INFO("COMMON", "Hello World\n");		
	LOG_DEBUG("COMMON", "Hello World\n");		
	LOG_TRACE_IN("COMMON", "Hello World\n");
	LOG_TRACE_OUT("COMMON", "Hello World\n");

	char c,*cp,*sp,str[][64] = {"I", "See", "Everyting"};
	float f,*fp, fl;
	int *ip;
#if 1
	t_gen l1 = create_link_list("INT DLL",eDOUBLE_LINKLIST, eINT32);
	t_gen l2 = create_link_list("CHAR SLL",eSINGLE_LINKLIST, eINT8);
	t_gen l3 = create_link_list("FLOAT SCLL",eSINGLE_CIRCULAR_LINKLIST, eFLOAT);
	t_gen l4 = create_link_list("STRING DCLL",eDOUBLE_CIRCULAR_LINKLIST, eSTRING);
//	t_gen l5 = create_link_list("FLOAT XORLL",eXOR_LINKLIST, eFLOAT);
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		((t_linklist*)l2)->add(l2, assign_char(c));

		((t_linklist*)l1)->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		((t_linklist*)l3)->add(l3, assign_float(f));

		((t_linklist*)l4)->add(l4, assign_string(str[i]));
//		((t_linklist*)l5)->add(l5, assign_float(f));
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
//	print_link_list(l5);
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
//		fp = ((t_linklist*)l5)->del(l5, &f);
//		free(fp);
	}

	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
//	print_link_list(l5);
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		((t_linklist*)l2)->append(l2, assign_char(c));

		((t_linklist*)l1)->append(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		((t_linklist*)l3)->append(l3, assign_float(f));

		((t_linklist*)l4)->append(l4, assign_string(str[i]));
//		((t_linklist*)l5)->append(l5, assign_float(f));
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
//	print_link_list(l5);

	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		((t_linklist*)l2)->add(l2, assign_char(c));

		((t_linklist*)l1)->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		((t_linklist*)l3)->add(l3, assign_float(f));

		((t_linklist*)l4)->add(l4, assign_string(str[i]));
//		((t_linklist*)l5)->add(l5, assign_float(f));
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
//	print_link_list(l5);

	for (i = 2; i >= 0; i--) {
		cp = ((t_linklist*)l2)->del_idx(l2, i);
		//printf("%c\n", *cp);
		free_mem(cp);

		ip = ((t_linklist*)l1)->del_idx(l1, i);
		//printf("%d\n",*ip);
		free_mem(ip);

		f= (float)i+0.222 / 2.0f;
		fp = ((t_linklist*)l3)->del_idx(l3, i);
		//printf("%f\n", *fp);
		free_mem(fp);

		sp = ((t_linklist*)l4)->del_idx(l4, i);
		//printf("%s\n",sp);
		free_mem(sp);
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);

	destroy_link_list(l1);
	destroy_link_list(l2);
	destroy_link_list(l3);
	destroy_link_list(l4);

	t_gen s1 = create_stack("Up Stack", 10, eARRAY_STACK, eINT32);
	t_gen s2 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, eINT8);
	t_gen s3 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, eFLOAT);
	t_gen s4 = create_stack("Up Stack LL", 10, eLL_STACK, eFLOAT);
	for(i = 0; i < 10; i++) {
		((t_stack*)s1)->push(s1, assign_int(i));
		c= 'c' + i;
		((t_stack*)s2)->push(s2, assign_char(c));
		f= (float)i+0.222 / 2.0f;
		((t_stack*)s3)->push(s3, assign_float(f));
		fl= (float)i+0.222 / 2.0f;
		((t_stack*)s4)->push(s4, assign_float(fl));
	}
	print_stack(s1);
	print_stack(s2);
	print_stack(s3);
	print_stack(s4);
	for(i = 0; i < 4; i++) {
		ip = ((t_stack*)s1)->pop(s1);
		free_mem(ip);
		cp = ((t_stack*)s2)->pop(s2);
		free_mem(cp);
		fp = ((t_stack*)s3)->pop(s3);
		free_mem(fp);
		fp = ((t_stack*)s4)->pop(s4);
		free_mem(fp);
	}
	print_stack(s1);
	print_stack(s2);
	print_stack(s3);
	print_stack(s4);
	for(i = 4; i > 0; i--) {
		((t_stack*)s1)->push(s1, assign_int(i));
		c= 'c' + i;
		((t_stack*)s2)->push(s2, assign_int(c));
		f= (float)i+0.222 / 2.0f;
		((t_stack*)s3)->push(s3, assign_float(f));
		fl= (float)i+0.222 / 2.0f;
		((t_stack*)s4)->push(s4, assign_float(fl));
	}
	print_stack(s1);
	print_stack(s2);
	print_stack(s3);
	print_stack(s4);
	destroy_stack(s1);
	destroy_stack(s2);
	destroy_stack(s3);
	destroy_stack(s4);
#endif
	t_gen q1 = create_queue("Queue1", 10, eARRAY_QUEUE_CIRC, eINT8);
	t_gen q2 = create_queue("Queue2", 10, eARRAY_QUEUE_CIRC, eFLOAT);

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

	mem_finit();

	return 0;

}
