/*
 * @Author: LiuHao
 * @Date: 2024-05-02 13:50:42
 * @Description: 
 */
#ifndef _VM_VM_H
#define _VM_VM_H

#include "common.h"

#define NUM_TEST 2

#define OPCODE_SLOTS(opcode, effect) OPCODE_##opcode,
typedef enum {
    #include "../scripts/opcode.inc"
} OpCode;
#undef OPCODE_SLOTS

struct vm {
    uint32_t allocatedBytes; // 累计已分配的内存量
    Parser *curParser; // 当前词法分析器
    // ObjHeader *allObjects; // 所有已分配对象链表
    // SymbolTable allMethodNames; // 所有类的方法名
    // ObjMap *allModules;
    // ObjThread *curThread; // 当前正在执行的线程

    // Class *classOfClass;
    // Class *objectClass;
    // Class *mapClass;
    // Class *rangeClass;
    // Class *listClass;
    // Class *fnClass;
    // Class *stringClass;
    // Class *nullClass;
    // Class *boolClass;
    // Class *numClass;
    // Class *threadClass;
};

void InitVMM(VM *vm);
VM* NewVMM(void);

#endif // !_VM_VM_H