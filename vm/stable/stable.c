#include "stable.h"


/**
 * @brief 在table中查找符号，找到返回索引
*/
int GetIndexFromSymbolTable(SymbolTable *table, const char *symbol, uint32_t length)
{
    uint32_t index = 0;
    while (index < table->count) {
        if (length == table->datas[index].length && memcmp(table->datas[index].str, symbol, length) == 0) {
            return index;
        }
        index ++;
    }
    return -1;
}

/**
 * @brief 在table中添加符号symbol 返回其索引
*/
int AddSymbol(VM *vm, SymbolTable *table, const char *symbol, uint32_t length)
{
    String string;
    string.str = ALLOCATE_ARRAY(vm, char, length + 1);
    memcpy(string.str, symbol, length);
    string.str[length] = '\0';
    string.length = length;
    StringBufferAdd(vm, table, string);
    return table->count - 1;
}