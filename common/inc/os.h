#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <signal.h>

#ifndef CUSTOM_MALLOC
	#define os_alloc(nmemb, size)				calloc((count, (size))
	#define os_free(mem_addr)						free((mem_addr))

#endif
