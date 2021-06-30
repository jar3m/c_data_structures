/*! @file logger.c
    @brief 
    Contains definitions of routines for logger module
*/

#include "common.h"
#include "logger.h"

//Array to maintain current log levels to be used
static bool log_level[MAX_LOG_LEVELS] = {false};
static bool module_logs[MAX_MODULES] = {false};

/*! @brief  
 *   Initailize logger module
 *  @return 	- NA
 * */
void logger_init()
{
	int i;
	
	for (i = 0; i < MAX_LOG_LEVELS; i++) {
		log_level[i] = true;
	}

	printf("Logger init\n");

}

/*! @brief  
 *   Used for defining different logging modules such as warn, error, debug, trace ...
 *  @return 	- NA
 * */
int app_log(char *module, int level, char *prefix, const char *format, ...)
{
	int len = 0;
	va_list args;

	va_start(args, format);

	if (level < MAX_LOG_LEVELS && log_level[level] == true) {
		char time_buff[64];
		int millisec;
		struct timeval tv;
		time_t now = time(0);

		gettimeofday(&tv, NULL);
		millisec = (tv.tv_usec/1000);
		strftime(time_buff, 64, "%H:%M:%S", localtime(&now));
		printf("%s.%03d ", time_buff, millisec);
		switch (level) {
			case __LOG_ERROR__:
				printf("[ERR");
				break;
			case __LOG_WARN__:
				printf("[WRN");
				break;
			case __LOG_INFO__:
				printf("[INF");
				break;
			case __LOG_DEBUG__:
				printf("[DBG");
				break;
			case __LOG_TRACE__:
				printf("[TRC");
				break;
			default:
				printf("[UDF");
				break;
		}

		printf(":%s] ",module);

		if (prefix != NULL) {
			printf("{%s} ", prefix);
		}
		len = vprintf(format, args);
	}

	va_end(args);

	return len;
}
