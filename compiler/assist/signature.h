/*
 * @Author: LiuHao
 * @Date: 2024-05-03 18:51:07
 * @Description: 
 */
#ifndef _COMPILE_SIGNATURE_H

#define _COMPILE_SIGNATURE_H

#include <stdint.h>

/**
 * SIGN_CONSTRUCT
 * SIGN_METHOD
 * SIGN_GETTER
 * SIGN_SETTER
 * SIGN_SUBSCRIPT 表示getter形式的下标，即把[]处理为方法，如list[1]
 * SIGN_SUBSCRIPT_SETTER 同上list[1]="1"
*/
typedef enum {
    SIGN_CONSTRUCT, SIGN_METHOD, SIGN_GETTER, SIGN_SETTER, SIGN_SUBSCRIPT, SIGN_SUBSCRIPT_SETTER
} SignatureType; // 方法的签名

typedef struct {
    SignatureType type;
    const char *name;
    uint32_t length;
    uint32_t argNum;
} Signature; // 签名

#endif // !_COMPILE_SIGNATURE_H