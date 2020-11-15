#include "common.h"

static t_mem_manager memer; 

void mem_init() 
{ 
  memer.mem_record = NULL;
	memer.alloc_count = 0;
	memer.free_count = 0;
}

void mem_finit(void) 
{
	t_mem_record *iter = NULL;
  mem_alloc_report();
	if (memer.mem_record != NULL) {
		for (iter = memer.mem_record ; iter != NULL; iter = iter->next) {
		  printf("cleaning up allocated memory space %p\n", iter);
			os_free(iter);
		}
	}
	memer.alloc_count = 0;
	memer.free_count = 0;

}

void *tag_alloc(size_t nmemb, size_t size, char *file, int line)
{
	//TODO:add resource lock
	t_mem_record *new_mem = os_alloc(1, sizeof(t_mem_record));
	if (new_mem == NULL) {
		printf("Memory allocation for tracker failed\n");
	}
  new_mem->nmemb = nmemb;
	new_mem->block_size = size;
	new_mem->file = file;
	new_mem->line = line;
  new_mem->next = NULL;

	new_mem->mem = os_alloc(nmemb, size);
	if (new_mem->mem == NULL) {
		printf("Memory allocation failed\n");
	}
	else {
		memer.alloc_count++;
		new_mem->next = memer.mem_record;
		memer.mem_record = new_mem;
	}


	return (new_mem->mem);

}
		



void untag_alloc(void *mem_addr, char *file, int line)
{
	t_mem_record * mem_list = NULL, *prev_addr = NULL;
	if (memer.mem_record == NULL)
		return;

	for (mem_list = memer.mem_record; mem_list != NULL; prev_addr = mem_list, mem_list = mem_list->next) {
		if (mem_addr == mem_list->mem) {
			
			if (mem_addr == memer.mem_record->mem) {
				memer.mem_record = mem_list->next;
			}
			else {
				prev_addr->next = mem_list->next;
			}

			if (mem_addr)	{
				os_free(mem_addr);
				memer.free_count++;
			}
		
		os_free(mem_list);
		}
	}
}


void mem_alloc_report(void)
{
	printf("allocations = %4d , freed allocations = %4d\n", 
	           memer.alloc_count, memer.free_count);
}
