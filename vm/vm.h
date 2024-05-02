/*
 * @Author: LiuHao
 * @Date: 2024-05-02 13:50:42
 * @Description: 
 */
#ifndef _VM_VM_H
#define _VM_VM_H

#define NUM_TEST 2

#define OPCODE_SLOTS(opcode, effect) OPCODE_##opcode,
typedef enum {
    #include "../scripts/opcode.inc"
} OpCode;
#undef OPCODE_SLOTS

#endif // !_VM_VM_H