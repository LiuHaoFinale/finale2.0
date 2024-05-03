/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:29:55
 * @Description: 
 */
#ifndef _COMMON_UTILS_H
#define _COMMON_UTILS_H

#include "common.h"
#include "alloc.h"

typedef struct {
    char *str;
    uint32_t length;
} String;

typedef struct {
    uint32_t length; // 除结束\0之外的字符个数
    char start[0]; // 类似c99中的柔性数组
} CharValue; // 字符串缓冲区

// 声明buffer类型
#define DECLARE_BUFFER_TYPE(type) \
    typedef struct { \
        type* datas; \
        uint32_t count; \
        uint32_t capacity; \
    } type##Buffer; \
    void type##BufferInit(type##Buffer *buf); \
    void type##BufferFillWrite(VM *vm, type##Buffer *buf, type data, uint32_t fillCount); \
    void type##BufferAdd(VM *vm, type##Buffer *buf, type data); \
    void type##BufferClear(VM *vm, type##Buffer *buf);

// 定义buffer方法
#define DEFINE_BUFFER_METHOD(type) \
    void type##BufferInit(type##Buffer *buf) \
    { \
        buf->datas = NULL; \
        buf->count = buf->capacity = 0; \
    } \
    void type##BufferFillWrite(VM *vm, type##Buffer *buf, type data, uint32_t fillCount) \
    { \
        uint32_t newCounts = buf->capacity + fillCount; \
        if (newCounts > buf->capacity) { \
            size_t oldSize = buf->capacity * sizeof(type); \
            buf->capacity = CeilToPowerOf2(newCounts); \
            size_t newSize = buf->capacity * sizeof(type); \
            buf->datas = (type *)MemManager(vm, buf->datas, oldSize, newSize); \
        } \
        uint32_t cnt = 0; \
        while (cnt < fillCount) { \
            buf->datas[buf->count ++] = data; \
            cnt ++; \
        } \
    } \
    void type##BufferAdd(VM *vm, type##Buffer *buf, type data) \
    { \
        type##BufferFillWrite(vm, buf, data, 1); \
    } \
    void type##BufferClear(VM *vm, type##Buffer *buf) \
    { \
        size_t oldSize = buf->capacity * sizeof(buf->datas[0]); \
        MemManager(vm, buf->datas, oldSize, 0); \
        type##BufferInit(buf); \
    }

typedef uint8_t Byte;
typedef char    Character;
typedef int     Integer;
#define SymbolTable StringBuffer

DECLARE_BUFFER_TYPE(String)
DECLARE_BUFFER_TYPE(Character)
DECLARE_BUFFER_TYPE(Byte)
DECLARE_BUFFER_TYPE(Integer)

uint32_t CeilToPowerOf2(uint32_t v);
void SymbolTableClear(VM*, SymbolTable* buffer);

char* GetSystemTime(void);

#endif // !_COMMON_UTILS_H