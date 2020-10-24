#include "common.h"

int main(int argc, char *argv[])
{
	printf("Hello World\n");

	logger_init();
	fault_manager_init(NULL);

	return 0;

}
