#include "obj_range.h"

/**
 * @brief 新建range对象
*/
ObjRange* NewObjRange(VM *vm, int from, int to)
{
    ObjRange *objRange = ALLOCATE(vm, ObjRange);
    InitObjHeader(vm, &objRange->objHeader, OT_RANGE, vm->rangeClass);
    objRange->from = from;
    objRange->to = to;
    return objRange;
}