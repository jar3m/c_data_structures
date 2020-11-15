#include "common.h"

int main(int argc, char *argv[])
{

	printf("Hello Memers\n");
	mem_init();
	logger_init();
	size_t size = 0;
	int *ptr[100];
	for (int i = 0; i < 100; i ++) {
	 ptr[i] = (int *)get_mem(1, sizeof(int));
	 size += sizeof(*(ptr[i]));
	 printf("address of allocated memory = %p\n", ptr[i]);
	}
	printf("size of allocated memory = %lu\n" , size);
  for (int i = 0; i < 100; i++) {
		del_mem(ptr[i]);
	}


	LOG_ERROR("COMMON", "Hello World\n");
	LOG_WARN("COMMON", "Hello World\n");		
	LOG_INFO("COMMON", "Hello World\n");		
	LOG_DEBUG("COMMON", "Hello World\n");		
	LOG_TRACE_IN("COMMON", "Hello World\n");
	LOG_TRACE_OUT("COMMON", "Hello World\n");

	fault_manager_init(NULL);
	mem_finit();

	return 0;

}
