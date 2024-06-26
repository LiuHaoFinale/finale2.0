/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:49:16
 * @Description: 
 */
#ifndef _VM_CORE_H
#define _VM_CORE_H

#include "common.h"
#include "class.h"
#include "obj_fn.h"
#include "header_obj.h"

extern char* rootDir;

#define CORE_MODULE VT_TO_VALUE(VT_NULL)

char* ReadFile(const char *path);
ObjThread* LoadModule(VM *vm, Value moduleName, const char *moduleCode);
ObjModule* GetModule(VM *vm, Value moduleName);
void BuildCore(VM *vm);
VMResult ExecuteModule(VM *vm, Value moduleName, const char *moduleCode);
int DefineModuleVar(VM *vm, ObjModule *objModule, const char *name, uint32_t length, Value value);

#endif //!_VM_CORE_H