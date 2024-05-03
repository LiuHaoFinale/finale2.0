#ifndef _CLASS_LIST_H

#define _CLASS_LIST_H

#include "class.h"
#include "vm.h"
#include "header_obj.h"

typedef struct {
    ObjHeader objHeader;
    ValueBuffer elements; 
} ObjList;

ObjList* NewObjList(VM *vm, uint32_t elementNum);
Value RemoveElement(VM *vm, ObjList *objList, uint32_t index);
void InsertElement(VM *vm, ObjList *objList, uint32_t index, Value value);

#endif // !_CLASS_LIST_H