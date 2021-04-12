#include "common.h"
#include "link_list.h"

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

	t_gen l1 = create_link_list("SLL",eSINGLE_LINKLIST);
	t_gen l2 = create_link_list("DLL",eDOUBLE_LINKLIST);
	t_gen l3 = create_link_list("SCLL",eSINGLE_CIRCULAR_LINKLIST);
	t_gen l4 = create_link_list("DCLL",eDOUBLE_CIRCULAR_LINKLIST);
	for (i = 0; i < 3; i++) {
		((t_linklist*)l1)->add(l1, i);
		((t_linklist*)l2)->add(l2, i);
		((t_linklist*)l3)->add(l3, i);
		((t_linklist*)l4)->add(l4, i);
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
	LOG_INFO("TEST", "deleting nodes in link list\n");
	for (i = 0; i < 3; i++) {
		((t_linklist*)l1)->del(l1, i);
		((t_linklist*)l2)->del(l2, i);
		((t_linklist*)l3)->del(l3, i);
		((t_linklist*)l4)->del(l4, i);
	}

	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
	for (i = 0; i < 3; i++) {
		((t_linklist*)l1)->append(l1, i);
		((t_linklist*)l2)->append(l2, i);
		((t_linklist*)l3)->append(l3, i);
		((t_linklist*)l4)->append(l4, i);
	}
	print_link_list(l1);
	print_link_list(l2);
	print_link_list(l3);
	print_link_list(l4);
	destroy_link_list(l1);
	destroy_link_list(l2);
	destroy_link_list(l3);
	destroy_link_list(l4);
	mem_finit();


	return 0;

}
