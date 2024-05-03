/*
 * @Author: LiuHao
 * @Date: 2024-05-03 00:57:46
 * @Description: 
 */
#include "compiler.h"
#include "parser.h"

/**
 * @brief 初始化compileunit
*/
void InitCompileUnit(Parser *parser, CompileUnit *cu, CompileUnit *enclosingUnit, boolean isMethod)
{
    parser->curCompileUnit = cu;
    cu->curParser = parser;
    cu->enclosingUnit = enclosingUnit;
    cu->curLoop = NULL;
    cu->enclosingClassBK = NULL;

    /**
     * 如果没有外层直接编译单元，说明当前属于模块作用域
    */
    if (enclosingUnit == NULL) {
        // 编译代码时是从上到下最外层的模块作用域开始，模块作用域为-1
        cu->scopeDepth = -1;
        // 模块级作用域中没有局部变量
        cu->localVarNum = 0;
    } else {
        if (isMethod) {
            // 如果是类中的方法
            cu->localVars[0].name = "this";
            cu->localVars[0].length = 4;
        } else { // 如果是普通函数 
            // 空出第0个局部变量，保持统一
            cu->localVars[0].name = NULL;
            cu->localVars[0].length = 0;
        }
        // 第0个局部变量比较特殊，使其作用域为-1
        cu->localVars[0].scopeDepth = -1;
        cu->localVars[0].isUpvalue = false;
        cu->localVarNum = 1;
        cu->scopeDepth = 0; // TODO
    }
    // 局部变量保存在栈中，初始时栈中已使用的slot数量等于局部变量的数量
    cu->stackSlotsNum = cu->localVarNum;

    cu->compileUnitFn = NewObjFn(cu->curParser->vm, cu->curParser->curModule, cu->localVarNum);
}

/**
 * @brief 编译模块
*/
ObjFn* CompileModule(VM *vm, ObjModule *objModule, const char *moduleCore)
{
    // 各源码模块文件需要单独的parser 分配一个parser
    Parser parser;
    parser.parent = vm->curParser;
    // TODO: 局部变量带出去，当出栈时，该变量会被释放
    vm->curParser = &parser;

    // 获得一个parser，每一个module都有一个parser
    if (objModule->name == NULL) { // 核心模块的name是NULL
        // 核心模块是core.script.inc
        // 与BuildCore内容基本相同，不同的是此处用脚本文件实现
        InitParser(vm, &parser, "core.script.inc", moduleCore, objModule);
    } else {
        InitParser(vm, &parser,  (const char *)objModule->name->value.start, moduleCore, objModule);
    }
    
    // 初始化一个compileUnit
    CompileUnit moduleCu;
    // 分配一个compileunit
    InitCompileUnit(&parser, &moduleCu, NULL, false);
    // 记录现在模块变量的数量，后面检查预定义模块变量时可减少遍历
    uint32_t moduleVarNumBefor = objModule->moduleVarValue.count;
    // 初始的parser->curToken.type为TOKEN_UNKNOWN,下面使其指向第一个合法的token
    GetNextToken(&parser);

    // 读Token
    while (!MatchToken(&parser, TOKEN_EOF)) {
        CompileProgram(&moduleCu);
    }

    // 模块编译完成，生成return null返回
    WriteOpcode(&moduleCu, OPCODE_PUSH_NULL);
    WriteOpcode(&moduleCu, OPCODE_RETURN);

    // 检查在函数id中用行号生命的模块变量是否在引用之后有定义

    // 模块编译完成，当前编译单元置空
    vm->curParser->curCompileUnit = NULL;
    vm->curParser = vm->curParser->parent; // 回到父解析器
#ifdef DEBUG
    return EndCompileUnit(&moduleCu, "(script)", 8);
#else
    return EndCompileUnit(&moduleCu);
#endif
}

/**
 * @brief 编译程序 编译的入口
*/
void CompileProgram(CompileUnit *cu)
{
    if (MatchToken(cu->curParser, TOKEN_CLASS)) {
        CompileClassDefinition(cu);
    } else if (MatchToken(cu->curParser, TOKEN_FUN)) {
        CompileFunctionDefinition(cu);
    } else if (MatchToken(cu->curParser, TOKEN_VAR)) {
        CompileVarDefinition(cu, cu->curParser->preToken.type == TOKEN_STATIC);
    } else if (MatchToken(cu->curParser, TOKEN_IMPORT)) {
        CompileImport(cu);
    } else {
        CompileStatement(cu);
    }
}