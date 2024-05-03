/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:15:16
 * @Description: 
 */
#ifndef _FINALE_LOG_H
#define _FINALE_LOG_H

#include <stdio.h>

#define NONE  "\e[0m"       // none
#define RED   "\e[0;31m"    // error
#define GREEN  "\e[0;32m"   // info
#define YELLOW "\e[1;33m"   // warning
#define BLUE "\e[0;34m"     // debug
#define REVERSE "\e[7m"     // 

// 用于调测
#ifdef FINALE_LOG   /* 在编译的时候加上-D定义宏_D即可 */
#define FLOG_SHOW(fmt, args...) printf(fmt, ##args)
#else
#define FLOG_SHOW(fmt, args...)
#endif

typedef enum {
    INFO_LOG, ERROR_LOG, WARNING_LOG, DEBUG_LOG
} LogLevel;

void log_info(const char *fmt, ...);
void log_error(const char *fmt, ...);
void log_warning(const char *fmt, ...);
void log_debug(const char *fmt, ...);

#endif // !_FINALE_LOG_H