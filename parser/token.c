/*
 * @Author: LiuHao
 * @Date: 2024-05-02 21:14:48
 * @Description: 
 */
#include "token.h"

KeywordToken g_keywordToken[] = {
    {"var",      3,     TOKEN_VAR},
    {"fun",      3,     TOKEN_FUN},
    {"if",       2,      TOKEN_IF},
    {"else",     4,    TOKEN_ELSE},
    {"true",     4,    TOKEN_TRUE},
    {"false",    5,   TOKEN_FALSE},
    {"while",    5,   TOKEN_WHILE},
    {"for",      3,     TOKEN_FOR},
    {"break",    5,   TOKEN_BREAK},
    {"continue", 8,TOKEN_CONTINUE},
    {"return",   6,  TOKEN_RETURN},
    {"null",     4,    TOKEN_NULL},
    {"class",    5,   TOKEN_CLASS},
    {"is",       2,      TOKEN_IS},
    {"static",   6,  TOKEN_STATIC},
    {"this",     4,    TOKEN_THIS},
    {"super",    5,   TOKEN_SUPER},
    {"import",   6,  TOKEN_IMPORT},
    {NULL,       0, TOKEN_UNKNOWN}
};

// TODO:针对全局变量的访问，不应直接访问