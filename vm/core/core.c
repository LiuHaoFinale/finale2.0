/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:49:18
 * @Description: 
 */
#include "core.h"
#include "exec.h"
#include "merror.h"
#include "compiler.h"
#include "class.h"
#include "class_config.h"
#include "prim_obejct.h"
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

char *rootDir = NULL; // 根目录

char* ReadFile(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        IO_ERROR("Could't open file \"%s\".", path);
    }

    struct stat fileStat;
    stat(path, &fileStat);
    size_t fileSize = fileStat.st_size;
    char *fileContent = (char *)malloc(fileSize + 1);
    if (fileContent == NULL) {
        MEM_ERROR("Could't allocate memory for reading file \"%s\".\n", path);
    }

    size_t numRead = fread(fileContent, sizeof(char), fileSize, file);
    if (numRead < fileSize) {
        IO_ERROR("Could't read file \"%s\".\n", path);
    }
    fileContent[fileSize] = '\0';

    fclose(file);
    // printf("%s", file_content);
    return fileContent;
}

/**
 * @brief 编译核心模块
 * @details 在读取源码文件之前，先编译核心模块
*/
void BuildCore(VM *vm)
{
    ObjModule *coreModule = NewObjModule(vm, NULL); // NULL为核心模块
    // 创建核心模块，录入vm->allModule  {vt_null: coremodule}
    MapSet(vm, vm->allModules, CORE_MODULE, OBJ_TO_VALUE(coreModule));
    
    /**
     * 此处有两处绑定到coreModule，将objectClass和objectMetaClass类初始化后
     * 因为每个vm对应一个ObjModule，所以将其绑定到coreModule的模块变量
    */

    // 创建object类并绑定方法 放入coreModule->moduleVarName
    vm->objectClass = DefineClass(vm, coreModule, "object");
    PRIM_METHOD_BIND(vm->objectClass, "!", PrimObjectNot);
    PRIM_METHOD_BIND(vm->objectClass, "==(_)", PrimObjectEqual);
    PRIM_METHOD_BIND(vm->objectClass, "!=(_)", PrimObjectNotEqual);
    PRIM_METHOD_BIND(vm->objectClass, "Is(_)", PrimObjectIs);
    PRIM_METHOD_BIND(vm->objectClass, "ToString", PrimClassToString);
    PRIM_METHOD_BIND(vm->objectClass, "Type", PrimObjectType);

    // 定义classOfClass类，它是所有meta类的meta类和基类
    vm->classOfClass = DefineClass(vm, coreModule, "class");

    // object_class是任何类的基类，此处绑定objectClass为classOfClass的基类
    BindSuperClass(vm, vm->classOfClass, vm->objectClass);

    PRIM_METHOD_BIND(vm->classOfClass, "Name", PrimClassName);
    PRIM_METHOD_BIND(vm->classOfClass, "SuperType", PrimClassSuperType);
    PRIM_METHOD_BIND(vm->classOfClass, "ToString", PrimClassToString);

    // object类的元信息类obejctMeta
    Class *objectMetaClass = DefineClass(vm, coreModule, "obejctMeta");
    // class_of_class类是所有meta类的meta类和基类
    BindSuperClass(vm, objectMetaClass, vm->classOfClass);

    PRIM_METHOD_BIND(objectMetaClass, "Same(_,_)", PrimObjectMetaSame);

    // 绑定各自的meta类
    vm->objectClass->objHeader.classPtr = objectMetaClass;
    objectMetaClass->objHeader.classPtr = vm->classOfClass;
    vm->classOfClass->objHeader.classPtr = vm->classOfClass; // 元信息类回路，meta类终点

    ExecuteModule(vm, CORE_MODULE, coreModule); // 核心模块在此处执行
}

/**
 * @brief 载入模块module_name并编译
*/
ObjThread* LoadModule(VM *vm, Value moduleName, const char *moduleCode)
{
    ObjModule *module = GetModule(vm, moduleName);
    // 避免重复载入
    if (module == NULL) {
        ObjString *modName = VALUE_TO_OBJSTR(moduleName);

        module = NewObjModule(vm, modName->value.start);
        MapSet(vm, vm->allModules, moduleName, OBJ_TO_VALUE(module));

        // 继承核心模块中的变量
        ObjModule *coreModule = GetModule(vm, CORE_MODULE);
        uint32_t idx = 0;
        while (idx < coreModule->moduleVarName.count) {
            DefineModuleVar(vm, module, 
                coreModule->moduleVarName.datas[idx].str, 
                strlen(coreModule->moduleVarName.datas[idx].str), 
                coreModule->moduleVarValue.datas[idx]);
            idx ++;
        }
    }
    
    /**
    * 为函数创建闭包并放到线程中
    * 闭包是函数和其环境组成的实体，为函数提供了自由变量的存储空间
    */
    ObjFn *fn = CompileModule(vm, module, moduleCode); // 生成的指令流存入fn中
    ObjClosure *objClosure = NewObjClosure(vm, fn); // 创建闭包
    ObjThread *moduleThread = NewObjThread(vm, objClosure); // 根据闭包创建线程

    return moduleThread;
    return NULL;
}

/**
 * @brief 从module中获取名为module_name的模块
*/
ObjModule* GetModule(VM *vm, Value moduleName)
{
    Value value = MapGet(vm->allModules, moduleName);
    if (value.valueType == VT_UNDEFINED) {
        return NULL;
    }

    return VALUE_TO_OBJMODULE(value);
}

 /**
 * @brief 在模块objModule中定义名为name，值为value的模块变量
 *          模块变量存储在objModule结构体中
*/
int DefineModuleVar(VM *vm, ObjModule *objModule, const char *name, uint32_t length, Value value)
{
    if (length > MAX_ID_LEN) {
        char id[MAX_ID_LEN] = {'\0'};
        memcpy(id, name, length);
        /**
         * 本函数可能是在编译源码文件之前调用的，那时还没有创建parser
        */
        if (vm->curParser != NULL) {
            COMPILE_ERROR(vm->curParser, "length of identifier \"%s\" should be no more than %d", id, MAX_ID_LEN);
        } else { // 编译源码前调用，比如加载核心模块时会调用此函数
            MEM_ERROR("length of identifier \"%s\" should be no more than %d", id, MAX_ID_LEN);
        }
    }
    int symbolIndex= GetIndexFromSymbolTable(&objModule->moduleVarName, name, length);
    if (symbolIndex == -1) {
        symbolIndex = AddSymbol(vm, &objModule->moduleVarName, name, length);
        ValueBufferAdd(vm, &objModule->moduleVarValue, value);
    } else if (VALUE_IS_NUM(objModule->moduleVarValue.datas[symbolIndex])) {
        objModule->moduleVarValue.datas[symbolIndex] = value;
    } else {
        symbolIndex = -1;
    }
    return symbolIndex;          
}