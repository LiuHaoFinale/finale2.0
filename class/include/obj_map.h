/*
 * @Author: LiuHao
 * @Date: 2024-05-03 01:00:03
 * @Description: 
 */
#ifndef _CLASS_MAP_H

#define _CLASS_MAP_H

#include "header_obj.h"

#define MAP_LOAD_PERCENT 0.8

typedef struct {
    Value key;
    Value value;
} Entry; // key value对儿

typedef struct {
    ObjHeader objHeader;
    uint32_t count;
    uint32_t capacity; // map的容量
    Entry *entries; // Entry数组
} ObjMap;

ObjMap* NewObjMap(VM *vm);

void MapSet(VM *vm, ObjMap *objMap, Value key, Value value);
Value MapGet(ObjMap *objMap, Value key);
void ClearMap(VM *vm, ObjMap *objMap);
Value RemoveKey(VM *vm, ObjMap *objMap, Value key);

#endif // !_CLASS_MAP_H