/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:30:00
 * @Description: 
 */
#include "utils.h"
#include <time.h>
#include <stdlib.h>

uint32_t CeilToPowerOf2(uint32_t v)
{
    v += (v == 0);
    v --;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v ++;
    return v;
}

DEFINE_BUFFER_METHOD(String)
DEFINE_BUFFER_METHOD(Integer)
DEFINE_BUFFER_METHOD(Character)
DEFINE_BUFFER_METHOD(Byte)

void SymbolTableClear(VM* vm, SymbolTable* buffer) {
   uint32_t idx = 0;
   while (idx < buffer->count) {
      MemManager(vm, buffer->datas[idx++].str, 0, 0); 
   }
   StringBufferClear(vm, buffer);
}

char* GetSystemTime(void)
{
   time_t rawTime;
   struct tm *info;

   time(&rawTime);
   info = localtime(&rawTime);

   char *buffer = (char *)malloc(sizeof(char) * 20U);
   strftime(buffer, sizeof(char) * 20U, "%Y-%m-%d %H:%M:%S", info);

   return buffer;
}