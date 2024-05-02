#include "vm.h"

void InitVMM(VM *vm)
{
    vm->allocatedBytes = 0;
    vm->curParser = NULL;
}

VM* NewVMM(void)
{
    VM *vm = (VM *)malloc(sizeof(VM));
    if (vm == NULL) {
        MEM_ERROR("Allocate vm Fail!");
    }
    InitVM(vm);
    // BuildCore(vm); // 在读取源码之前先编译核心模块
    return vm;
}