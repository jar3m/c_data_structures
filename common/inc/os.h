#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>


#ifndef CUSTOM_MALLOC
	#define os_alloc(nmemb, size)				calloc((nmemb), (size))
	#define os_free(mem_addr)						free((mem_addr))

#endif
