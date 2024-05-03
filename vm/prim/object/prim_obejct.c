/*
 * @Author: LiuHao
 * @Date: 2024-05-03 13:34:05
 * @Description: 
 */
#include "prim_obejct.h"
#include "class.h"

/**
 * @brief object取反
*/
boolean PrimObjectNot(VM *vm UNUSED, Value *args)
{
    RET_VALUE(VT_TO_VALUE(VT_FALSE));
}

boolean PrimObjectEqual(VM *vm UNUSED, Value *args)
{
    Value boolValue = BOOL_TO_VALUE(ValueIsEqual(args[0], args[1]));
    RET_VALUE(boolValue);
}

boolean PrimObjectNotEqual(VM *vm UNUSED, Value *args)
{
    Value boolValue = BOOL_TO_VALUE(!ValueIsEqual(args[0], args[1]));
    RET_VALUE(boolValue);
}

/**
 * @brief 类args[0]是否为类args[1]的子类
*/
boolean PrimObjectIs(VM *vm, Value *args)
{
    if (!VALUE_IS_CLASS(args[1])) {
        RUNTIME_ERROR("Argument must be class!");
    }
    
    Class *thisClass = GetClassOfObj(vm, args[0]);
    Class *baseClass = (Class *)(args[1].objHeader);

    // 也有可能是多级继承
    while (baseClass != NULL) {
        if (thisClass == baseClass) {
            RET_VALUE(VT_TO_VALUE(VT_TRUE));
        }
        baseClass = baseClass->superClass;
    }

    // 找不到
    RET_VALUE(VT_TO_VALUE(VT_FALSE));
}

/**
 * @brief 返回args[0]所属class的名字
*/
boolean PrimObjectToString(VM *vm UNUSED, Value *args)
{
    Class *classPtr = args[0].objHeader->classPtr;
    Value nameValue = OBJ_TO_VALUE(classPtr->name);
    RET_VALUE(nameValue);
}

/**
 * @brief 返回对象args[0]所属的类
*/
boolean PrimObjectType(VM *vm, Value *args)
{
    Class *classPtr = GetClassOfObj(vm, args[0]);
    RET_OBJ(classPtr);
}

/**
 * @brief 返回类名
*/
boolean PrimClassName(VM *vm UNUSED, Value *args)
{
    RET_OBJ(VALUE_TO_CLASS(args[0])->name);
}

/**
 * @brief 返回args[0]的基类
*/
boolean PrimClassSuperType(VM *vm UNUSED, Value *args)
{
    Class *classPtr = VALUE_TO_CLASS(args[0]);
    if (classPtr->superClass != NULL) {
        RET_OBJ(classPtr->superClass);
    }
    RET_VALUE(VT_TO_VALUE(VT_NULL));
}

/**
 * @brief 返回类名
*/
boolean PrimClassToString(VM *vm UNUSED, Value *args)
{
    RET_OBJ(VALUE_TO_CLASS(args[0])->name);
}

/**
 * @brief 返回args[1]和args[2]是否相等
*/
boolean PrimObjectMetaSame(VM *vm UNUSED, Value *args)
{
    Value boolValue = BOOL_TO_VALUE(ValueIsEqual(args[1], args[2]));
    RET_VALUE(boolValue);
}