/*
 * @Author: LiuHao
 * @Date: 2024-05-03 20:59:13
 * @Description: 
 */
#include "oper.h"
#include "compiler.h"

/**
 * @brief 在函数的指令流中写入1字节，返回其索引
*/
int WriteByte(CompileUnit *cu, int byte)
{
#ifdef DEBUG
    IntegerBufferAdd(cu->curParser->vm, &cu->compileUnitFn->debug->lineNo, cu->curParser->preToken.lineNo);
#endif
    ByteBufferAdd(cu->curParser->vm, &cu->compileUnitFn->instructStream, (uint8_t) byte);
    return cu->compileUnitFn->instructStream.count - 1;
}

/**
 * @brief 写入操作码
*/
void WriteOpcode(CompileUnit *cu, OpCode opcode)
{
    WriteByte(cu, opcode);

    cu->stackSlotsNum += opCodeSlotsUsed[opcode];
    if (cu->stackSlotsNum > cu->compileUnitFn->maxStackSlotUsedNum) {
        cu->compileUnitFn->maxStackSlotUsedNum = cu->stackSlotsNum; // 记录栈使用的峰值
    }
}

/**
 * @brief 写入1字节的操作数
*/
int WriteByteOperand(CompileUnit *cu, int operand)
{
    return WriteByte(cu, operand);
}

/**
 * @brief 写入2个字节的操作数，按大端字节序写入参数
*/
void WriteShortOperand(CompileUnit *cu, int operand)
{
    WriteByte(cu, (operand >> 8) & 0xff);
    WriteByte(cu, operand & 0xff);
}

/**
 * @brief 写入操作数为1字节大小的指令
*/
int WriteOpcodeByteOperand(CompileUnit *cu, OpCode opcode, int operand)
{
    WriteOpcode(cu, opcode);
    return WriteByteOperand(cu, operand);
}

/**
 * @brief 写入操作数为2字节大小的指令
*/
void WriteOpcodeShortOperand(CompileUnit *cu, OpCode opcode, int operand)
{
    WriteOpcode(cu, opcode);
    WriteShortOperand(cu, operand);
}