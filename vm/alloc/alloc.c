/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:40:45
 * @Description: 
 */
#include "alloc.h"
#include "vm.h"

void* MemManager(VM *vm, void *ptr, uint32_t oldSize, uint32_t newSize)
{
    vm->allocatedBytes += newSize - oldSize;
    if (newSize == 0) {
        free(ptr);
        return NULL;
    }

    return realloc(ptr, newSize);
}