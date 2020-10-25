#ifndef _LOGGER_H
#define _LOGGER_H

#define __LOG_ERROR__		0
#define __LOG_WARN__		1
#define __LOG_INFO__		2
#define __LOG_DEBUG__		3
#define __LOG_TRACE__		4

#define MAX_LOG_LEVELS	5
#define MAX_MODULES			4
#define	COMMON_MODULE		1

#define LOG_ERROR(fmt, args...)			app_log(COMMON_MODULE, __LOG_ERROR__, NULL, fmt, ##args)
#define LOG_WARN(fmt, args...)			app_log(COMMON_MODULE, __LOG_WARN__, NULL, fmt, ##args)
#define LOG_INFO(fmt, args...)			app_log(COMMON_MODULE, __LOG_INFO__, NULL, fmt, ##args)
#define LOG_DEBUG(fmt, args...)			app_log(COMMON_MODULE, __LOG_DEBUG__, NULL, fmt, ##args)
#define LOG_TRACE_IN(fmt, args...)		app_log(COMMON_MODULE, __LOG_TRACE__, NULL, "[++%s:%4d]" fmt"\n", __func__, __LINE__, ##args)
#define LOG_TRACE_OUT(fmt, args...)		app_log(COMMON_MODULE, __LOG_TRACE__, NULL, "[--%s:%4d]" fmt"\n", __func__, __LINE__, ##args)

void logger_init();
int app_log(int module, int level, char *prefix, const char *format, ...);

#endif // End of _LOGGER_H
