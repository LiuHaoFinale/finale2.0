/*
 * @Author: LiuHao
 * @Date: 2024-05-02 17:26:21
 * @Description: 
 */
#ifndef _COMMON_COMMON_H
#define _COMMON_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct class Class;
typedef struct parser Parser;
typedef struct vm VM;

#define boolean char
#define true 1
#define false 0
#define UNUSED __attribute__ ((unused))

#define NOT_REACHED() \
    do { \
        fprintf(stderr, "NOT_REACHED: %s: %d In function %s()\n", \
                __FILE__, __LINE__, __func__); \
        while (1); \
    } while (0);

#endif // !_COMMON_COMMON_H