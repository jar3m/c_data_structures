#pragma once 

#define get_mem(nmemb, size) tag_alloc(nmemb, size,  __FILE__, __LINE__)
#define free_mem(mem_addr) untag_alloc(mem_addr, __FILE__, __LINE__) 
#define FREE_MEM untag_alloc

typedef struct memory_record 
{
	void *mem;
	size_t nmemb;
	size_t block_size;
	char *file;
	int line;
	struct memory_record *next;
}t_mem_record;


typedef struct mem_mamnager{
	t_mem_record *mem_record;
	int alloc_count;
	int free_count;
}t_mem_manager;


void mem_init(void);
void mem_finit(void);

void *tag_alloc(size_t nmemb, size_t size, char *file, int line);
void untag_alloc(void *mem_addr, char *file, int line);

void mem_alloc_report(void);

