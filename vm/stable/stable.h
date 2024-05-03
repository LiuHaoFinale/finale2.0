/*
 * @Author: LiuHao
 * @Date: 2024-05-03 20:21:35
 * @Description: symbol table operation
 */
#ifndef _VMM_STABLE_H

#define _VMM_STABLE_H

#include "common.h"
#include "utils.h"

int AddSymbol(VM *vm, SymbolTable *table, const char *symbol, uint32_t length);
int GetIndexFromSymbolTable(SymbolTable *table, const char *symbol, uint32_t length);

#endif //!_VMM_STABLE_H