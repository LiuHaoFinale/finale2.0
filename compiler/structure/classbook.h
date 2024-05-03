#ifndef _COMPILE_CLASSBOOK_H

#define _COMPILE_CLASSBOOK_H

#include "common.h"
#include "obj_string.h"
#include "signature.h"

typedef struct {
    ObjString *name;
    SymbolTable fields; // 类属性符号表
    boolean inStatic; // 当前编译静态方法
    IntegerBuffer instantMethods; // 实例方法
    IntegerBuffer staticMethods; // 静态方法
    Signature *signature; // 当前正在编译的签名
} ClassBookKeep; // 用于记录类编译时的信息

#endif //!_COMPILE_CLASSBOOK_H