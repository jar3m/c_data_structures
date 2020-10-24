#include <fault_manager.h>
static struct sigaction action = {0};

void dummy_fault_handler()
{

	// closing_logger_manager
	// closing_memory_manager
	// gracefulexit
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



