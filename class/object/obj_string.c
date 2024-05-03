/*
 * @Author: LiuHao
 * @Date: 2024-05-03 01:00:28
 * @Description: 
 */
#include "obj_string.h"
#include "common.h"
#include "utils.h"
#include "merror.h"
#include "vm.h"
#include <string.h>

/**
 * @brief fnv-la算法
*/
uint32_t HashString(char *str, uint32_t length)
{
    uint32_t hashCode = 2166136261, idx = 0;
    while (idx < length) {
        hashCode ^= str[idx];
        hashCode *= 16777619;
        idx ++;
    }
    return hashCode;
}

/**
 * @brief 为string计算哈希码并将值存储到string->hash
*/
void HashObjString(ObjString *objString)
{
    objString->hashCode = HashString(objString->value.start, objString->value.length);
}

/**
 * @brief 以str字符串创建Objstring对象，允许空串""
*/
ObjString* NewObjString(VM *vm, const char *str, uint32_t length)
{
    // ALLOCATE_EXTRA用于柔性数组的分配
    ObjString *objString = ALLOCATE_EXTRA(vm, ObjString, length + 1);

    if (objString != NULL) {
        // stringClass为meta类
        InitObjHeader(vm, &objString->objHeader, OT_STRING, vm->stringClass);
        objString->value.length = length;

        // 支持空字符串:str为null，length为0
        if (length > 0) {
            memcpy(objString->value.start, str, length);
        }
        objString->value.start[length] = '\0'; // 最后一个，即length + 1长度的1
        HashObjString(objString); // 获得该字符串的哈希码
    } else {
        MEM_ERROR("Allocating ObjString failed!");
    }
    return objString;
}