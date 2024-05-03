#ifndef _COMPILE_LOCALVAR_H

#define _COMPILE_LOCALVAR_H

#include "common.h"

typedef struct {
    const char *name;
    uint32_t length;
    int scopeDepth; // 局部变量作用域
    // 表示本函数中的局部变量是否是其内层函数所引用的upvalue
    // 则为true
    boolean isUpvalue;
} LocalVar; // 局部变量

#endif // !_COMPILE_LOCALVAR_H