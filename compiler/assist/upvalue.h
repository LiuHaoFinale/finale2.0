/*
 * @Author: LiuHao
 * @Date: 2024-05-03 18:50:56
 * @Description: 
 */
#ifndef _COMPILE_UPVALUE_H

#define _COMPILE_UPVALUE_H

#include "common.h"
#include <stdint.h>

typedef struct {
    // 如果此upvalue是直接外层函数的局部变量就置为true
    boolean isEnclosingLocalVar;
    // 外层函数中局部变量的索引或者外层函数中的upvalue索引
    // 这去决定于is_enclosing_local_var的值
    uint32_t index;
} Upvalue;

#endif // !_COMPILE_UPVALUE_H