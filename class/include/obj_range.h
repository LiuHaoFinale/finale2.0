/*
 * @Author: LiuHao
 * @Date: 2024-05-03 01:00:13
 * @Description: 
 */
#ifndef _CLASS_RANGE_H

#define _CLASS_RANGE_H

#include "class.h"

typedef struct {
    ObjHeader objHeader;
    int from;
    int to;
} ObjRange;

ObjRange* NewObjRange(VM *vm, int from, int to);

#endif // !_CLASS_RANGE_H