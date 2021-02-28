#include "common.h"
#include <execinfo.h>

static struct sigaction action = {0};

void dummy_fault_handler()
{

	void *array[10];
	size_t size;

	//get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	// gracefulexit
	// closing_logger_manager
	
	// closing_memory_manager
	mem_finit();

	printf("gracefullexit\n");
}

void default_fault_handler(int signo, siginfo_t *info, void *extra)
{
	printf("Signal %d received\n", signo);
	dummy_fault_handler();
	abort();
}



void fault_manager_init(f_fault_handle handler)
{

	if (handler == NULL) {
		printf("fault_handler_undefined using deafult_fault_handler\n");
		handler = default_fault_handler;
		
	}

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;

	if (sigaction(SIGFPE, &action, NULL) == -1) {
		perror("sigfpe: sigaction");
		exit(1);
	}
	if (sigaction(SIGSEGV, &action, NULL) == -1) {
		perror("sigsegv: sigaction");
		exit(1);
	}
	if (sigaction(SIGILL, &action, NULL) == -1) {
		perror("sigill: sigaction");
		exit(1);
	}
	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigint: sigaction");
		exit(1);
	}
	if (sigaction(SIGTERM, &action, NULL) == -1) {
		perror("sigterm: sigaction");
		exit(1);
	}
}

/* TODO enchancment:
- mechanism for handling multiple signals
- mechanism mutiple handlers for multiple signals
- create fault_manager close
- module to register routine to be called when fault
- 

*/



