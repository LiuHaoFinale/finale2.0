/*
 * @Author: LiuHao
 * @Date: 2024-05-03 00:57:43
 * @Description: 
 */
#ifndef _COMPILER_COMPILER_H

#define _COMPILER_COMPILER_H

#include "obj_fn.h"

#define MAX_LOCAL_VAR_NUM   128
#define MAX_UPVALUE_NUM     128
#define MAX_ID_LEN          128  // 变量名最大长度

#define MAX_METHOD_NAME_LEN MAX_ID_LEN
#define MAX_ARG_NUM 16

// 函数名长度+'('+n个参数+(n-1)个参数分隔符','+')'
#define MAX_SIGN_LEN MAX_METHOD_NAME_LEN + MAX_ARG_NUM * 2 + 1

#define MAX_FIELD_NUM 128

#endif //!_COMPILER_COMPILER_H