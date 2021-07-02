/*! @file fault_manager.c
    @brief 
    Contains definitions of fault manager routines
*/

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

/*! @brief  
 *  Defaul fault handler called on any of the signals initialised to be handled
 *  @param signo - Signal number
 *  @param prm   - Signal info
 *  @param prm   - Signal dat
 *  @return      - NA
 * */
void default_fault_handler(int signo, siginfo_t *info, void *extra)
{
	printf("Signal %d received\n", signo);
	dummy_fault_handler();
	abort();
}


/*! @brief  
 *  Handles signals and faults
 *  depending on type of fault/signal occured
 *  @param prm  - User define fault handler
 *  @return     - NA
 * */
void fault_manager_init(f_fault_handle handler)
{
	// If no fault handler define use default
	if (handler == NULL) {
		printf("fault_handler_undefined using deafult_fault_handler\n");
		handler = default_fault_handler;
		
	}

	// Add signals to be handle
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;

	// Handle fatal arithmetic error such as floating pt exception
	if (sigaction(SIGFPE, &action, NULL) == -1) {
		perror("sigfpe: sigaction");
		exit(1);
	}
	// Handle segmentation fault
	if (sigaction(SIGSEGV, &action, NULL) == -1) {
		perror("sigsegv: sigaction");
		exit(1);
	}
	// Handles corrupted executable or stack overflow
	if (sigaction(SIGILL, &action, NULL) == -1) {
		perror("sigill: sigaction");
		exit(1);
	}
	// Handles interpts
	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigint: sigaction");
		exit(1);
	}
	// handles termination signal
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



