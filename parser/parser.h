/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:45:48
 * @Description: 
 */
#ifndef _PARSER_PARSER_H

#define _PARSER_PARSER_H

#include "common.h"
#include "token.h"
#include "obj_fn.h"
#include "compiler.h"

#define OPCODE_SLOTS(opCode, effect) effect,
static const int opCodeSlotsUsed[] = {
    #include "../scripts/opcode.inc"
};
#undef OPCODE_SLOTS

typedef struct parser {
    const char *file;
    const char *sourceCode;
    const char *nextCharPtr;
    char curChar;
    Token curToken;
    Token preToken;
    ObjModule *curModule; // 当前正在编译的模块
    CompileUnit *curCompileUnit; // 当前编译单元
    int interpolationExpectRightParenNum;
    VM *vm;
    struct parser *parent; // 指向父parser
} Parser;

char LookAheadChar(Parser *parser);
void GetNextToken(Parser *parser);
boolean MatchToken(Parser *parser, TokenType expected);
void ConsumeCurToken(Parser *parser, TokenType expected, const char *errMsg);
void ConsumeNextToken(Parser *parser, TokenType expected, const char * errMsg);
void InitParser(VM *vm, Parser *parser, const char *file, const char *sourceCode, ObjModule *objModule);

#endif //!_PARSER_PARSER_H