#ifndef LOGGER_H
#define LOGGER_H
/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file
 * @brief
 *
 **********************************************************************************************************************/


/* INCLUDES ***********************************************************************************************************/
#include <stdlib.h> //for malloc
#include <stdio.h>
#include <stdarg.h> //for variadic functions
#include <string.h> //for strcpy
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
/* Definitions ********************************************************************************************************/
#define LOGGER_PRINT_TERMINAL
/**
 * @def FERROR
 * macro to wrap fprintf(stderr, fmt, msg)
 * printed [ERROR] and file, func and line where was called
 * @param msg msg to print
 */
#define FERROR(msg)         fprintf(stderr, "[ ERROR ] %s %s %d: %s", __FILE__, __func__, __LINE__, msg)

/**
 * @def FFATAL
 * macro to wrap fprintf(stderr, fmt, msg)
 * printed [FATAL] and file, func and line where was called
 * @param msg msg to print
 */
#define FFATAL(msg)         fprintf(stderr, "[ FATAL ] %s %s %d: %s", __FILE__, __func__, __LINE__, msg)

/**
 * @def LOG_DEBUG(...)
 * @def LOG_FATAL(...)
 * @def LOG_ERROR(...)
 * @def LOG_WARNING(...)
 * @def LOG_INFO(...)
 * is used to wrap function logger_log,
 * @param ... arg like in printf(), fmt is required
 */
#ifndef LOGGER_DISABLE
#define LOG_DEBUG(...)      logger_log(LT_DEBUG, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...)      logger_log(FATAL, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...)      logger_log(ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...)    logger_log(WARNING, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)       logger_log(INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#define LOG_FATAL(...)
#define LOG_ERROR(...)
#define LOG_WARNING(...)
#define LOG_INFO(...)
#endif

#define AUTHOR      ("Piotr Miszta")
#define VERSION     ("1.0")
#define NAME        ("Server on RPi 3B")
/* Type Declarations **************************************************************************************************/
/**
 * @enum LoggerTypeE
 * specify type of logging message
 * DEBUG, INFO, WARNING, ERROR, FATAL
 */
typedef enum LoggerTypeE {
    LT_DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
}LoggerTypeE;

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/

/**
 * @brief logger_init()
 * initialize logger, allocating memory for logger variables
 * and save header of logger file
 * @param filename specify file name of logger
 */
void logger_init(const char* filename);

/**
 * @brief logger_destroy()
 * destructor for logger
 */
void logger_destroy(void);

/**
 * @brief logger_log
 * function save to file specified msg
 * @param logType type of logger entry
 * @param file in which *.c or *.h file logger was called
 * @param func in which function logger was called
 * @param line in which line logger was called
 * @param ... arg like printf(), fmt is requied
 */
void logger_log(LoggerTypeE logType, const char* file, const char* func, int line, ...);

/**
 * @brief logger_thread
 * function to call when starting logger thread when LOGGER_NO_THREAD is not defined
 * @param arg - NULL
 * @return null pointer
 */
void* logger_thread(void* arg);

/**
 * @brief logger_close
 * function close file and exit thread if LOGGER_NO_THREAD are not defined
 *
 */
void logger_close(void);

#endif //LOGGER_H
