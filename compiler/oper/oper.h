#ifndef __COMPILER_OPER_H

#define __COMPILER_OPER_H

#include "common.h"
#include "vm.h"

int WriteByte(CompileUnit *cu, int byte);
void WriteOpcode(CompileUnit *cu, OpCode opcode);
int WriteByteOperand(CompileUnit *cu, int operand);
void WriteShortOperand(CompileUnit *cu, int operand);
int WriteOpcodeByteOperand(CompileUnit *cu, OpCode opcode, int operand);
void WriteOpcodeShortOperand(CompileUnit *cu, OpCode opcode, int operand);

#endif //!__COMPILER_OPER_H