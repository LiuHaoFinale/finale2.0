/*
 * @Author: LiuHao
 * @Date: 2024-05-03 00:59:19
 * @Description: 
 */
#include "meta_obj.h"
#include "class.h"
#include "vm.h"
#include "common.h"
#include "merror.h"
#include <string.h>

/**
 * @brief 新建模块
*/
ObjModule* NewObjModule(VM *vm, const char *modName)
{
    ObjModule *objModule = ALLOCATE(vm, ObjModule); // ALLOCATE用于申请内存
    if (objModule == NULL) {
        MEM_ERROR("Allocate ObjModule Failed!");
    }

    // ObjModule是元信息对象，不属于任何一个类
    InitObjHeader(vm, &objModule->objHeader, OT_MODULE, NULL);
    
    StringBufferInit(&objModule->moduleVarName); // 初始化module的moduleVarName属性
    ValueBufferInit(&objModule->moduleVarValue); // 初始化module的moduleVarValue属性

    objModule->name = NULL; // 核心模块名为NULL
    if (modName != NULL) {
        objModule->name = NewObjString(vm, modName, strlen(modName));
    }

    return objModule;
}

/**
 * @brief 创建类class的实例
*/
ObjInstance* NewObjInstance(VM *vm, Class *myClass)
{
    ObjInstance *objInstance = ALLOCATE_EXTRA(vm, ObjInstance, sizeof(Value) * myClass->fieldNum);

    InitObjHeader(vm, &objInstance->objHeader, OT_INSTANCE, myClass);
    // 初始化field为NULL
    uint32_t idx = 0;
    while (idx < myClass->fieldNum) {
        objInstance->fields[idx ++] = VT_TO_VALUE(VT_NULL);
    }
    return objInstance;
}