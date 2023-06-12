/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file logger.c
 * @brief Source file with logger functions implementation.
 *
 **********************************************************************************************************************/


/* INCLUDES ***********************************************************************************************************/
#include "logger.h"

/* Definitions ********************************************************************************************************/
#define LOGGER_NO_FILE
#define LOGGER_NO_THREAD
#define LOGGER_COLOR

#ifdef LOGGER_COLOR

#define RED             "\x1B[31m"
#define GREEN           "\x1B[32m"
#define BLUE            "\x1B[35m"
#define YELLOW          "\x1B[36m"
#define RESET           "\x1B[0m"

#else

#define RED
#define GREEN
#define BLUE
#define YELLOW
#define RESET

#endif

/* Type Declarations **************************************************************************************************/
typedef struct  Logger {         //808
    va_list list;               //24
    FILE* file;                 //8
    LoggerTypeE type;           //4
    int line;                   //4
    bool open;                  //1
#ifndef LOGGER_NO_THREAD        //920
    pthread_mutex_t mutex;      //40
    sem_t semFull;              //32
    sem_t semEmpty;             //32
    char padded__[10];
#else
    char padded__[2];
#endif
    char func[255];             //255
    char fileDesc[255];         //255
    char msg[255];              //255

}Logger;

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/
static Logger* logger;

/* Static Function Declarations ***************************************************************************************/
static void logger_print_terminal(void);
static void logger_print(void);

/* Global Function Definitions ****************************************************************************************/
void logger_init(const char* filename) {
    logger = malloc(sizeof(Logger));
    if(logger == NULL) {
        FERROR("Failed to initialize logger.");
        return;
    }
    logger->file = fopen(filename, "w" );
    if(logger->file == NULL) {
        FERROR("Failed to open logger file.");
        free(logger);
        logger = NULL;
        return;
    }
    /*
     *  Multithreathing init
     */
#ifndef LOGGER_NO_THREAD
    sem_init(&logger->semEmpty, 0, 0);
    sem_init(&logger->semFull, 0, 1);
    pthread_mutex_init(&logger->mutex, NULL);
#endif
    /*
     * Write file desc like name time version authors etc.
     */
    fprintf(logger->file, "AUTHOMATED CREATED LOGGER FILE\n");
    fprintf(logger->file, "Program created by: ");
    fprintf(logger->file, AUTHOR);
    fprintf(logger->file, "\n");
    fprintf(logger->file, "Program: ");
    fprintf(logger->file, NAME);
    fprintf(logger->file, "\n");
    fprintf(logger->file, "Version: ");
    fprintf(logger->file, VERSION);
    fprintf(logger->file, "\n");
    fprintf(logger->file, "Created: %s %s\n\n", __DATE__, __TIME__);

    logger->open = true;
}

void logger_close(void) {
    logger->open = false;
#ifndef LOGGER_NO_THREAD
    sem_post(&logger->semEmpty);
#else
    logger_destroy();
#endif
}

void logger_destroy(void) {
    if(logger == NULL) {
        return;
    }
    if(logger->file != NULL)
        fclose(logger->file);
#ifndef LOGGER_NO_THREAD
    sem_destroy(&logger->semFull);
    sem_destroy(&logger->semEmpty);
    pthread_mutex_destroy(&logger->mutex);
#endif
    free(logger);
    logger = NULL;
}

void logger_log(LoggerTypeE logType, const char* file, const char* func, int line, ...) {
    if(logger == NULL) {
        fprintf(stderr, "Logger is not initialized, call first logger_init()\n");
        return;
    }
    va_list list;
#ifndef LOGGER_NO_THREAD
    sem_wait(&logger->semFull);
    pthread_mutex_lock(&logger->mutex);
#endif
    // COPING TO LOGGER STRUCT MUST BE IN MUTEX AND SEMAPHORE

    va_start(list, line);
    char* m = va_arg(list, char*);
    va_copy(logger->list, list);
    va_end(list);
    strcpy(logger->fileDesc, file);
    strcpy(logger->func, func);
    strcpy(logger->msg, m);
    logger->line = line;
    logger->type = logType;
#ifndef LOGGER_NO_THREAD
    pthread_mutex_unlock(&logger->mutex);
    sem_post(&logger->semEmpty);
#else
    logger_print();
#endif
    logger_print_terminal();
}

#ifndef LOGGER_NO_THREAD
void* logger_thread(void* arg) {
    while(1) {
        sem_wait(&logger->semEmpty);
        if(!logger->open) {
            break;
        }
        pthread_mutex_lock(&logger->mutex);
        logger_print();
        pthread_mutex_unlock(&logger->mutex);
        sem_post(&logger->semFull);
    }
    logger_destroy();
    return NULL;
}
#endif
/* Static Function Definitions ****************************************************************************************/
void logger_print(void) {
    va_list copyOfLogger;
    va_copy(copyOfLogger, logger->list);
    switch (logger->type) {
        case LT_DEBUG:
            fprintf(logger->file, GREEN"[ DEBUG ] "RESET);
            break;
        case INFO:
            fprintf(logger->file, BLUE"[ INFO ] "RESET);
            break;
        case ERROR:
            fprintf(logger->file, RED"[ ERROR ] "RESET);
            fprintf(stderr, "[ ERROR ] %s %s %d:", logger->fileDesc, logger->func, logger->line);
            vfprintf(stderr, logger->msg, copyOfLogger);
            fprintf(stderr, "\n");
            break;
        case WARNING:
            fprintf(logger->file, YELLOW"[ WARNING ] "RESET);
            break;
        case FATAL:
            fprintf(logger->file, RED"[ FATAL ] "RESET);
            fprintf(stderr, "[FATAL ] %s %s %d:", logger->fileDesc, logger->func, logger->line);
            vfprintf(stderr, logger->msg, copyOfLogger);
            fprintf(stderr, "\n");
            break;
    }
    fprintf(logger->file, "%s %s ", __DATE__, __TIME__);
#ifndef LOGGER_NO_FILE
    fprintf(logger->file, "%s ", logger->fileDesc);
#endif //LOGGER_NO_FILE
    fprintf(logger->file, "%s ", logger->func);
    fprintf(logger->file, "%d ", logger->line);
    vfprintf(logger->file, logger->msg, copyOfLogger);
    fprintf(logger->file, "\n");
    va_end(copyOfLogger);
}

void logger_print_terminal(void)
{
    va_list copyOfLogger;
    va_copy(copyOfLogger, logger->list);
    switch (logger->type) {
        case LT_DEBUG:
            fprintf(stdout, GREEN"[ DEBUG ] "RESET);
            break;
        case INFO:
            fprintf(stdout, BLUE"[ INFO ] "RESET);
            break;
        case ERROR:
            fprintf(stdout, RED"[ ERROR ] "RESET);
            fprintf(stderr, "[ ERROR ] %s %s %d:", logger->fileDesc, logger->func, logger->line);
            vfprintf(stderr, logger->msg, copyOfLogger);
            fprintf(stderr, "\n");
            break;
        case WARNING:
            fprintf(stdout, YELLOW"[ WARNING ] "RESET);
            break;
        case FATAL:
            fprintf(stdout, RED"[ FATAL ] "RESET);
            fprintf(stderr, "[FATAL ] %s %s %d:", logger->fileDesc, logger->func, logger->line);
            vfprintf(stderr, logger->msg, copyOfLogger);
            fprintf(stderr, "\n");
            break;
    }
    fprintf(stdout, "%s %s ", __DATE__, __TIME__);
#ifndef LOGGER_NO_FILE
    fprintf(logger->file, "%s ", logger->fileDesc);
#endif //LOGGER_NO_FILE
    fprintf(stdout, "%s ", logger->func);
    fprintf(stdout, "%d: ", logger->line);
    vfprintf(stdout, logger->msg, copyOfLogger);
    fprintf(stdout, "\n");
    va_end(copyOfLogger);
}
