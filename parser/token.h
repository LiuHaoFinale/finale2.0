/*
 * @Author: LiuHao
 * @Date: 2024-05-02 20:18:43
 * @Description: 
 */
#ifndef _PARSER_TOKEN_H

#define _PARSER_TOKEN_H

#include "common.h"
#include "header_obj.h"

#define PEEK_TOKEN(parserPtr) parserPtr->curToken.type

typedef enum {
    TOKEN_UNKNOWN, TOKEN_NUM, TOKEN_STRING, TOKEN_ID, TOKEN_INTERPOLATION,
    TOKEN_VAR, TOKEN_FUN, TOKEN_IF, TOKEN_ELSE, TOKEN_TRUE, TOKEN_FALSE, TOKEN_WHILE, TOKEN_FOR, TOKEN_BREAK,
                TOKEN_CONTINUE, TOKEN_RETURN, TOKEN_NULL,
    TOKEN_CLASS, TOKEN_THIS, TOKEN_STATIC, TOKEN_IS, TOKEN_SUPER, TOKEN_IMPORT,
    TOKEN_COMMA, TOKEN_COLON, TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN, TOKEN_LEFT_BRACKET, TOKEN_RIGHT_BRACKET,
                TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE, TOKEN_DOT, TOKEN_DOT_DOT,
    TOKEN_ADD, TOKEN_SUB, TOKEN_MUL, TOKEN_DIV, TOKEN_MOD,
    TOKEN_ASSIGN,
    TOKEN_BIT_AND, TOKEN_BIT_OR, TOKEN_BIT_NOT, TOKEN_BIT_SHIFT_RIGHT, TOKEN_BIT_SHIFT_LEFT,
    TOKEN_LOGIC_AND, TOKEN_LOGIC_OR, TOKEN_LOGIC_NOT,
    TOKEN_EQUAL, TOKEN_NOT_EQUAL, TOKEN_GREAT, TOKEN_GREAT_EQUAL, TOKEN_LESS, TOKEN_LESS_EQUAL,
    TOKEN_QUESTION,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type; // Token类型
    const char *start; 
    uint32_t length; // 长度
    uint32_t lineNo; // 行号
    Value value; // 用于存储单词的值
} Token;

typedef struct KeywordToken {
    char *keyword;
    uint8_t length;
    TokenType token;
} KeywordToken;  // 关键字(保留字)结构

extern KeywordToken g_keywordToken[];

#endif //!_PARSER_TOKEN_H