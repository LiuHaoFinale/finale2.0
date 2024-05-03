/*
 * @Author: LiuHao
 * @Date: 2024-05-03 13:34:02
 * @Description: 
 */
#ifndef _VMM_PRIM_OBJECT_H

#define _VMM_PRIM_OBJECT_H

#include "common.h"
#include "header_obj.h"

boolean PrimObjectNot(VM *vm UNUSED, Value *args);
boolean PrimObjectEqual(VM *vm UNUSED, Value *args);
boolean PrimObjectNotEqual(VM *vm UNUSED, Value *args);
boolean PrimObjectIs(VM *vm, Value *args);
boolean PrimObjectToString(VM *vm UNUSED, Value *args);
boolean PrimObjectType(VM *vm, Value *args);
boolean PrimClassName(VM *vm UNUSED, Value *args);
boolean PrimClassSuperType(VM *vm UNUSED, Value *args);
boolean PrimClassToString(VM *vm UNUSED, Value *args);
boolean PrimObjectMetaSame(VM *vm UNUSED, Value *args);

#endif // !_VMM_PRIM_OBJECT_H