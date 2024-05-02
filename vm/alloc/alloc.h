/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:40:28
 * @Description: 
 */
#ifndef _VM_ALLOC_H

#define _VM_ALLOC_H

#include "common.h"

#define ALLOCATE(vmPtr, type) \
    (type *)MemManager(vmPtr, NULL, 0, sizeof(type))

#define DEALLOCATE(vmPtr, memPtr) MemManager(vmPtr, memPtr, 0, 0)

// 用于柔性数组的内存分配
#define ALLOCATE_EXTRA(vmPtr, mainType, extraSize) \
    (mainType *)MemManager(vmPtr, NULL, 0, sizeof(mainType) + extraSize)

#define ALLOCATE_ARRAY(vmPtr, type, count) \
    (type *)MemManager(vmPtr, NULL, 0, sizeof(type) * count)

#define DEALLOCATE_ARRAY(vmPtr, arrayPtr, count) \
    MemManager(vmPtr, arrayPtr, sizeof(arrayPtr[0]) * count, 0)

void* MemManager(VM *vm, void *ptr, uint32_t oldSize, uint32_t newSize);

#endif // !_VM_ALLOC_H