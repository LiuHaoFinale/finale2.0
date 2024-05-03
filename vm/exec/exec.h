#ifndef _VMM_EXEC_H

#define _VMM_EXEC_H

#include "common.h"
#include "header_obj.h"
#include "vm.h"
#include "obj_thread.h"

VMResult ExecuteModule(VM *vm, Value moduleName, const char *moduleCode);
VMResult ExecuteInstruction(VM *vm, register ObjThread *curThread);

#endif //!_VMM_EXEC_H