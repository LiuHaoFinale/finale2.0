/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:32:35
 * @Description: 
 */
#include "error.h"
#include <stdarg.h>

/**
 * @brief 通用报错函数
*/
void ErrorReport(void *parser, ErrorType errorType, const char *fmt, ...)
{
    char buffer[DEFAULT_BUFFER_SIZE] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, DEFAULT_BUFFER_SIZE, fmt, ap);
    va_end(ap);

    switch (errorType) {
        case ERROR_IO:
        case ERROR_MEM:
            fprintf(stderr, "%s: %d In function %s(): %s\n", __FILE__, __LINE__, __func__, buffer);
            break;
        case ERROR_LEX:
        case ERROR_COMPILE:
    // #ifndef FINELA_TEST
    //         fprintf(stderr, "%s:%d \"%s\"\n", ((Parser *)parser)->file, ((Parser *)parser)->preToken.lineNo, buffer);
    // #else
    //         LOG_SHOW(RED"%s:%d \"%s\"\n" NONE, ((Parser *)parser)->file, ((Parser *)parser)->preToken.lineNo, buffer);
    // #endif
            break;
        case ERROR_RUNTIME:
            fprintf(stderr, "%s\n", buffer);
            break;
        default:
            NOT_REACHED();
    }
    exit(1);
}