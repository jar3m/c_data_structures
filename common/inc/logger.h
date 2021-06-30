/*! @file logger.h
    @brief 
    Defines Macros for logging 
*/
#pragma once

#define __LOG_ERROR__		0		///< log level Error
#define __LOG_WARN__		1		///< log level Warn
#define __LOG_INFO__		2		///< log level Info
#define __LOG_DEBUG__		3		///< log level Debug
#define __LOG_TRACE__		4		///< log level Trace

#define MAX_LOG_LEVELS		5
#define MAX_MODULES		4
#define	COMMON_MODULE		1

#define LOG_ERROR(mod,fmt, args...)			app_log(mod, __LOG_ERROR__, NULL, fmt, ##args)
#define LOG_WARN(mod, fmt, args...)			app_log(mod, __LOG_WARN__, NULL, fmt, ##args)
#define LOG_INFO(mod, fmt, args...)			app_log(mod, __LOG_INFO__, NULL, fmt, ##args)
#define LOG_DEBUG(mod, fmt, args...)			app_log(mod, __LOG_DEBUG__, NULL, fmt, ##args)
#define LOG_TRACE_IN(mod, fmt, args...)		app_log(mod, __LOG_TRACE__, NULL, "[++%s:%4d]" fmt"\n", __func__, __LINE__, ##args)
#define LOG_TRACE_OUT(mod, fmt, args...)		app_log(mod, __LOG_TRACE__, NULL, "[--%s:%4d]" fmt"\n", __func__, __LINE__, ##args)

void logger_init();
int app_log(char *module, int level, char *prefix, const char *format, ...);

