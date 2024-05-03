/*
 * @Author: LiuHao
 * @Date: 2024-05-03 18:51:45
 * @Description: 
 */
#ifndef _COMPILE_LOOP_H

#define _COMPILE_LOOP_H

typedef struct loop {
    int condStartIndex; // 条件地址
    int bodyStartIndex; // 起始地址
    int scopeDepth; 
    int exitIndex; // 不满足时的目标地址
    struct loop *enclosingLoop; // 外层循环
} Loop; // loop结构

#endif //!_COMPILE_LOOP_H