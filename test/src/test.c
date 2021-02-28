#include "common.h"
#include "link_list.h"

int main(int argc, char *argv[])
{
	size_t size = 0;
	int *ptr[100];

	mem_init();
	logger_init();
	fault_manager_init(NULL);
	for (int i = 0; i < 100; i ++) {
		ptr[i] = (int *)get_mem(1, sizeof(int));
		size += sizeof(*(ptr[i]));
	}
	printf("size of allocated memory = %lu\n" , size);
	for (int i = 0; i < 100; i++) {
		free_mem(ptr[i]);
	}


	LOG_ERROR("COMMON", "Hello World\n");
	LOG_WARN("COMMON", "Hello World\n");		
	LOG_INFO("COMMON", "Hello World\n");		
	LOG_DEBUG("COMMON", "Hello World\n");		
	LOG_TRACE_IN("COMMON", "Hello World\n");
	LOG_TRACE_OUT("COMMON", "Hello World\n");

//	t_data l = create_link_list(eSINGLE_LINKLIST);
//	print_link_list(l);
//	destroy_link_list(l);
	mem_finit();

	return 0;

}
