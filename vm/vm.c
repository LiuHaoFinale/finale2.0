/*
 * @Author: LiuHao
 * @Date: 2024-05-02 13:50:46
 * @Description: 
 */
#include "vm.h"
#include "merror.h"
#include "lhlog.h"
#include <time.h>

void InitVMM(VM *vm)
{
    vm->allocatedBytes = 0;
    vm->curParser = NULL;
    vm->allObjects = NULL;
    vm->stringClass = NULL;
}

VM* NewVMM(void)
{
    VM *vm = (VM *)malloc(sizeof(VM));
    if (vm == NULL) {
        MEM_ERROR("Allocate vm Fail!");
    }
    InitVMM(vm);
    // BuildCore(vm); // 在读取源码之前先编译核心模块
    return vm;
}

/**
 * @brief 释放虚拟机
*/
void FreeVMM(VM *vm)
{
    FLOG_SHOW(GREEN"Free VMM Sucessfully!" NONE);
}