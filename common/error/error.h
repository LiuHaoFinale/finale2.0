/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:32:33
 * @Description: COMMON_ERROR
 */
#ifndef _COMMON_ERROR_H
#define _COMMON_ERROR_H

#include "common.h"

#define DEFAULT_BUFFER_SIZE 512

/**
 * IO错误 内存错误 语法错误 编译错误 运行时错误
*/
typedef enum {
    ERROR_IO,
    ERROR_MEM,
    ERROR_LEX,
    ERROR_COMPILE,
    ERROR_RUNTIME
} ErrorType;

#define IO_ERROR(...) \
    ErrorReport(NULL, ERROR_IO, __VA_ARGS__)
#define MEM_ERROR(...) \
    ErrorReport(NULL, ERROR_MEM, __VA_ARGS__)
#define LEX_ERROR(parser, ...) \
    ErrorReport(NULL, ERROR_LEX, __VA_ARGS__)
#define COMPILE_ERROR(parser, ...) \
    ErrorReport(NULL, ERROR_COMPILE, __VA_ARGS__)
#define RUNTIME_ERROR(...) \
    ErrorReport(NULL, ERROR_RUNTIME, __VA_ARGS__)

void ErrorReport(void *parser, ErrorType error_type, const char *fmt, ...);

#endif // !_COMMON_ERROR_H