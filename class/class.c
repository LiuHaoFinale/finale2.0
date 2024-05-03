#include "class.h"
#include "common.h"
#include "obj_string.h"
#include "obj_range.h"
#include "core.h"
#include "vm.h"
#include "utils.h"
#include "compiler.h"
#include "merror.h"
#include <string.h>

DEFINE_BUFFER_METHOD(Method)

/**
 * @brief 判断a和b是否相等
*/
boolean ValueIsEqual(Value a, Value b)
{
    if (a.valueType != b.valueType) {
        return false;
    }
    if (a.valueType == VT_NUM) {
        return a.num == b.num;
    }
    if (a.objHeader == b.objHeader) {
        return true;
    }
    if (a.objHeader->type != b.objHeader->type) {
        return false;
    }
    if (a.objHeader->type == OT_STRING) {
        ObjString *strA = VALUE_TO_OBJSTR(a);
        ObjString *strB = VALUE_TO_OBJSTR(b);
        return (strA->value.length == strB->value.length && memcmp(strA->value.start, strB->value.start, strA->value.length) == 0);
    }
    if (a.objHeader->type == OT_RANGE) {
        ObjRange *rgA = VALUE_TO_OBJRANGE(a);
        ObjRange *rgB = VALUE_TO_OBJRANGE(b);
        return (rgA->from == rgB->from && rgA->to == rgB->to);
    }
    return false;
}

/**
 * @brief 新建裸类
 *          一般的类都有归属类，即圆心锡类meta-class，裸类是没有归属的类
*/
Class* NewRawClass(VM *vm, const char *name, uint32_t fieldNum)
{
    Class *classPtr = ALLOCATE(vm, Class);
    InitObjHeader(vm, &classPtr->objHeader, OT_CLASS, NULL);
    classPtr->name = NewObjString(vm, name, strlen(name));
    classPtr->fieldNum = fieldNum;
    classPtr->superClass = NULL; // 默认无父类
    MethodBufferInit(&classPtr->methods);
    return classPtr;
}

/**
 * @brief 获得对象obj所属的类
 *          数字等Value也被视为对象，因此参数为Value，获得对象obj所属的类
*/
inline Class* GetClassOfObj(VM *vm, Value object)
{
    switch (object.valueType) {
        case VT_NULL:
            return vm->nullClass;
        case VT_FALSE:
        case VT_TRUE:
            return vm->boolClass;
        case VT_NUM:
            return vm->numClass;
        case VT_OBJ:
            return VALUE_TO_OBJ(object)->classPtr;
        default:
            NOT_REACHED()
    }
    return NULL;
}

/**
 * @brief 创建一个类
*/
Class* NewClass(VM *vm, ObjString *className, uint32_t fieldNum, Class *superClass)
{
    #define MAX_METACLASS_LEN MAX_ID_LEN + 10
    char newClassName[MAX_METACLASS_LEN] = {'\0'};
    #undef MAX_METACLASS_LEN
    memcpy(newClassName, className->value.start, className->value.length);
    memcpy(newClassName + className->value.length, "metaclass", 10U);
    Class *metaClass = NewRawClass(vm, newClassName, 0);
    metaClass->objHeader.classPtr = vm->classOfClass;
    BindSuperClass(vm, metaClass, vm->classOfClass);
    memcpy(newClassName, className->value.start, className->value.length);
    newClassName[className->value.length] = '\0';
    Class *classPtr = NewRawClass(vm, newClassName, fieldNum);
    classPtr->objHeader.classPtr = metaClass;
    BindSuperClass(vm, classPtr, superClass);
    return classPtr;
}

/**
 * @brief 绑定基类
*/
void BindSuperClass(VM *vm, Class *subClass, Class *superClass)
{
    subClass->superClass = superClass;
    // 继承基类属性数
    subClass->fieldNum += superClass->fieldNum;

    uint32_t idx = 0;
    while (idx < superClass->methods.count) {
        BindMethod(vm, subClass, idx, superClass->methods.datas[idx]);
        idx ++;
    }
}

/**
 * @brief 绑定方法
*/
void BindMethod(VM *vm , Class *classPtr, uint32_t index, Method method)
{
    if (index >= classPtr->methods.count) {
        Method emptyPad = { MT_NONE, {0} };
        MethodBufferFillWrite(vm, &classPtr->methods, emptyPad, index - classPtr->methods.count + 1);
    }
    classPtr->methods.datas[index] = method;
}

/**
 * @brief 定义类
*/
static Class* DefineClass(VM *vm, ObjModule *objModule, const char *name)
{
    Class *class = NewRawClass(vm, name, 0);  // 创建类

    // 把类作为普通变量在模块中定义
    DefineModuleVar(vm, objModule, name, strlen(name), OBJ_TO_VALUE(class));
    return class;
}