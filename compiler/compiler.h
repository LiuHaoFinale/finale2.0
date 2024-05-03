/*
 * @Author: LiuHao
 * @Date: 2024-05-03 00:57:43
 * @Description: 
 */
#ifndef _COMPILER_COMPILER_H

#define _COMPILER_COMPILER_H

#include "obj_fn.h"
#include "localvar.h"
#include "loop.h"
#include "classbook.h"
#include "upvalue.h"
#include "parser.h"

#define MAX_LOCAL_VAR_NUM   128
#define MAX_UPVALUE_NUM     128
#define MAX_ID_LEN          128  // 变量名最大长度

#define MAX_METHOD_NAME_LEN MAX_ID_LEN
#define MAX_ARG_NUM 16

// 函数名长度+'('+n个参数+(n-1)个参数分隔符','+')'
#define MAX_SIGN_LEN MAX_METHOD_NAME_LEN + MAX_ARG_NUM * 2 + 1

#define MAX_FIELD_NUM 128

struct compileUnit {
    ObjFn *compileUnitFn; 
    LocalVar localVars[MAX_LOCAL_VAR_NUM];
    uint32_t localVarNum; 
    Upvalue upvalues[MAX_UPVALUE_NUM]; // 记录本层函数所引用的upvalue
    int scopeDepth;
    uint32_t stackSlotsNum; // 当前使用的slot个数
    Loop *curLoop;
    ClassBookKeep *enclosingClassBK;
    struct compileUnit *enclosingUnit; // 直接外层编译单元
    Parser *curParser;
};

ObjFn* CompileModule(VM *vm, ObjModule *objModule, const char *moduleCore);
void CompileProgram(CompileUnit *cu);

#endif //!_COMPILER_COMPILER_H