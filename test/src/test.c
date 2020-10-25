#include "logger.h"
#include "common.h"

int main(int argc, char *argv[])
{
	logger_init();
	LOG_ERROR("Hello World\n");
	LOG_WARN("Hello World\n");		
	LOG_INFO("Hello World\n");		
	LOG_DEBUG("Hello World\n");		
	LOG_TRACE_IN("Hello World\n");
	LOG_TRACE_OUT("Hello World\n");

	fault_manager_init(NULL);

	return 0;

}
