/*
 * @Author: LiuHao
 * @Date: 2024-05-03 20:13:37
 * @Description: 
 */
#ifndef _CLASS_CLASS_CONFIG_H
#define _CLASS_CLASS_CONFIG_H

// 返回值是Value类型，放在args[0]中
#define RET_VALUE(value) \
    do { \
        args[0] = value;\
        return true; \
    } while (0);

// 将obj转换为Value后作为返回值
#define RET_OBJ(obj_ptr) RET_VALUE(OBJ_TO_VALUE(obj_ptr))

#define RET_BOOL(boolean) RET_VALUE(BOOL_TO_VALUE(boolean))
#define RET_NUM(num) RET_VALUE(NUM_TO_VALUE(num))
#define RET_NULL RET_VALUE(VT_TO_VALUE(VT_NULL))
#define RET_TRUE RET_VALUE(VT_TO_VALUE(VT_TRUE))
#define RET_FALSE RET_VALUE(VT_TO_VALUE(VT_FALSE))

// 设置线程报错
#define SET_ERROR_FALSE(vmPtr, errMsg) \
    do { \
        vmPtr->curThread->errorObj = OBJ_TO_VALUE(NewObjString(vmPtr, errMsg, strlen(errMsg))); \
        return false; \
    } while (0);

// 绑定方法func到class_ptr的类
#define PRIM_METHOD_BIND(classPtr, methodName, func) \
{ \
    uint32_t length = strlen(methodName); \
    int globalIdx = GetIndexFromSymbolTable(&vm->allMethodNames, methodName, length); \
    if (globalIdx == -1) \
    { \
        globalIdx = AddSymbol(vm, &vm->allMethodNames, methodName, length);\
    } \
    Method method; \
    method.type = MT_PRIMITIVE; \
    method.primFn = func; \
    BindMethod(vm, classPtr, (uint32_t)globalIdx, method); \
}

#endif // !_CLASS_CLASS_CONFIG_H