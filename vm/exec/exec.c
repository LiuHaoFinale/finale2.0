/*
 * @Author: LiuHao
 * @Date: 2024-05-03 13:32:35
 * @Description: 
 */
#include "exec.h"
#include "obj_thread.h"

/**
 * @brief 编译模块
*/
VMResult ExecuteModule(VM *vm, Value moduleName, const char *moduleCode)
{
    ObjThread *objThread = LoadModule(vm, moduleName, moduleCode);
    return ExecuteInstruction(vm, objThread);
}

// /**
//  * @brief 执行指令
// */
VMResult ExecuteInstruction(VM *vm, register ObjThread *curThread)
{
}
//     vm->curThread = curThread;
//     register Frame* curFrame;
//     register Value* stackStart;
//     register uint8_t* ip;
//     ObjFn *objFn;
//     OpCode opCode;

//     // 定义操作运行时的栈
//     // esp是栈中下一个可写入数据的slot
//     #define PUSH(value) (*curThread->esp ++ = value)
//     #define POP() (*(-- curThread->esp))
//     #define DROP() (curThread->esp --)  // 丢掉栈顶元素
//     #define PEEK() (*(curThread->esp - 1)) // 获取栈顶数据
//     #define PEEK2() (*(curThread->esp - 2)) // 获得次栈顶的数据
//     // 读指令
//     #define READ_BYTE() (*ip ++)
//     #define READ_SHORT() (ip += 2, (uint16_t)(ip[-2] << 8 | ip[-1]))
//     #define STORE_CUR_FRAME() curFrame->ip = ip // 备份IP

//     // 加载最新的frame
//     #define LOAD_CUR_FRAME()  \
//         curFrame = &curThread->frames[curThread->usedFrameNum - 1]; \
//         stackStart = curFrame->stackStart; \
//         ip = curFrame->ip; \
//         objFn = curFrame->closure->fn;
//     #define DECODE loopStart: \
//         opCode = READ_BYTE(); \
//         switch (opCode)
//     #define CASE(shortOpCode) case OPCODE_##shortOpCode
//     #define LOOP() goto loopStart

//     LOAD_CUR_FRAME();
//     DECODE {
//         // 第一部分操作码
//         CASE(LOAD_LOCAL_VAR):
//             PUSH(stackStart[(uint8_t)READ_BYTE()]);
//             LOOP();
//         CASE(LOAD_THIS_FIELD): {

//         }
//         CASE(POP):
//             DROP();
//             LOOP();
//         CASE(PUSH_NULL):
//             PUSH(VT_TO_VALUE(VT_NULL));
//             LOOP();
//         CASE(PUSH_FALSE):
//             PUSH(VT_TO_VALUE(VT_FALSE));
//             LOOP();
//         CASE(PUSH_TRUE):
//             PUSH(VT_TO_VALUE(VT_TRUE));
//             LOOP();
//         CASE(STORE_LOCAL_VAR):
//             stackStart[(uint8_t)READ_BYTE()] = PEEK();
//             LOOP();
//         CASE(LOAD_CONSTANT):
//             PUSH(objFn->constants.datas[(uint16_t)READ_SHORT()]);
//             LOOP();
//         {
//             int argNum, index;
//             Value *args;
//             Class *classPtr;
//             Method *method;
//             CASE(CALL0):
//             CASE(CALL1):
//             CASE(CALL2):
//             CASE(CALL3):
//             CASE(CALL4):
//             CASE(CALL5):
//             CASE(CALL6):
//             CASE(CALL7):
//             CASE(CALL8):
//             CASE(CALL9):
//             CASE(CALL10):
//             CASE(CALL11):
//             CASE(CALL12):
//             CASE(CALL13):
//             CASE(CALL14):
//             CASE(CALL15):
//             CASE(CALL16): // 指令流 2字节的method索引
//                 argNum = opCode - OPCODE_CALL0 + 1; // 所调用方法的参数个数
//                 index = READ_SHORT(); // 方法名的索引
//                 args = curThread->esp - argNum; // 调用方法的参数数组
//                 classPtr = GetClassOfObj(vm, args[0]); // 调用方法所在的类
//                 goto invokeMethod;
//             CASE(SUPER0):
//             CASE(SUPER1):
//             CASE(SUPER2):
//             CASE(SUPER3):
//             CASE(SUPER4):
//             CASE(SUPER5):
//             CASE(SUPER6):
//             CASE(SUPER7):
//             CASE(SUPER8):
//             CASE(SUPER9):
//             CASE(SUPER10):
//             CASE(SUPER11):
//             CASE(SUPER12):
//             CASE(SUPER13):
//             CASE(SUPER14):
//             CASE(SUPER15):
//             CASE(SUPER16): // 指令流1 2字节的method索引 指令流2 2字节的基类常量索引
//                 argNum = opCode - OPCODE_SUPER0 + 1;
//                 index = READ_SHORT(); // 方法名的索引
//                 args = curThread->esp - argNum; // 调用方法的参数数组
//                 classPtr = VALUE_TO_CLASS(objFn->constants.datas[(uint16_t)READ_SHORT()]);
//             invokeMethod:
//                 if (((uint32_t)index > classPtr->methods.count) ||
//                    ((method = &classPtr->methods.datas[index])->type == MT_NONE)) {
//                     RUNTIME_ERROR("Method not found!\n");
//                 }
//                 switch (method->type) {
//                     case MT_PRIMITIVE: // 原生方法
//                         // TODO: 
//                     case MT_SCRIPT:  // 脚本方法
//                         STORE_CUR_FRAME();
//                         CreateFrame(vm, curThread, (ObjClosure *)method->type, argNum);
//                         LOAD_CUR_FRAME(); // 加载最新的页帧
//                         break;
//                     case MT_FN_CALL: // 处理函数调用
//                         // TODO: ASSERT()
//                         ObjFn *fn = VALUE_TO_OBJCLOSURE(args[0])->fn;
//                         // -1是去掉实例this
//                         if ((argNum - 1) < fn->argNum) {
//                             RUNTIME_ERROR("Argument less");
//                         }
//                         STORE_CUR_FRAME();
//                         CreateFrame(vm, curThread, (ObjClosure *)method->type, argNum);
//                         LOAD_CUR_FRAME(); // 加载最新的页帧
//                         break;
//                     default:
//                         NOT_REACHED(); // 不可达
//                 }
//             LOOP();
//         }
//         CASE(LOAD_UPVALUE): // 指令流1 upvalue的索引
//             PUSH(*((curFrame->closure->upvalues[(uint8_t)READ_BYTE()])->localVarPtr));
//             LOOP();
//         CASE(STORE_UPVALUE):
//             *((curFrame->closure->upvalues[(uint8_t)READ_BYTE()])->localVarPtr) = PEEK();
//             LOOP();
//         CASE(LOAD_MODULE_VAR):
//             PUSH(objFn->module->moduleVarValue.datas[(uint16_t)READ_SHORT()]);
//             LOOP();
//         CASE(STORE_MODULE_VAR):
//             objFn->module->moduleVarValue.datas[(uint16_t)READ_SHORT()] = PEEK();
//             LOOP();    
//         CASE(STORE_THIS_FIELD): {
//             // 栈顶：field值
//             // 指令流 1字节的field索引
//             uint8_t fieldIdx = READ_BYTE();
//             // TODO: assert()
//             ObjInstance *objInstance = VALUE_TO_OBJINSTANCE(stackStart[0]);
//             objInstance->fields[fieldIdx] = PEEK();
//             LOOP();
//         }
//         CASE(LOAD_FIELD): {
//             // 栈顶：实例对象
//             // 指令流 1字节的field索引
//             uint8_t fieldIdx = READ_BYTE(); // 获取待加兹安的字段索引
//             Value receiver = POP(); // 获取消息接收者
//             // TODO: assert()
//             ObjInstance *objInstance = VALUE_TO_OBJINSTANCE(receiver);
//             PUSH(objInstance->fields[fieldIdx]);
//             LOOP();
//         }
//         CASE(STORE_FIELD): {
//             // 栈顶：实例对象 次栈顶：field值
//             // 指令流 1字节的field索引
//             uint8_t fieldIdx = READ_BYTE(); // 获取待加兹安的字段索引
//             Value receiver = POP(); // 获取消息接收者
//             // TODO: assert()
//             ObjInstance *objInstance = VALUE_TO_OBJINSTANCE(receiver);
//             PUSH(objInstance->fields[fieldIdx]);
//             LOOP();
//         }
//         CASE(JUMP): {// 指令流 2字节的跳转正偏移量
//             int16_t offset = READ_SHORT();
//             // TODO: assert
//             ip += offset;
//             LOOP();
//         }
//         CASE(LOOP): {
//             int16_t offset = READ_SHORT();
//             // TODO: assert
//             ip -= offset;
//             LOOP();
//         }
//         CASE(JUMP_IF_FALSE): {
//             // 栈顶：跳转条件bool值
//             // 指令流 2字节的跳转偏移量
//             int16_t offset = READ_SHORT();
//             // TODO: assert
//             Value condition = POP();
//             if (VALUE_IS_FALSE(condition) || VALUE_IS_NULL(condition)) {
//                 ip -= offset;
//             }
//             LOOP();
//         }
//         CASE(AND): {
//             // 栈顶：跳转条件bool值
//             // 指令流 2字节的跳转偏移量
//             int16_t offset = READ_SHORT();
//             // TODO: assert
//             Value condition = PEEK();
//             if (VALUE_IS_FALSE(condition) || VALUE_IS_NULL(condition)) {
//                 ip -= offset; // 若条件为假则不再计算and的右操作数
//             } else {
//                 DROP();
//             }
//             LOOP();
//         }
//         CASE(OR): {
//             // 栈顶：跳转条件bool值
//             // 指令流 2字节的跳转偏移量
//             int16_t offset = READ_SHORT();
//             // TODO: assert
//             Value condition = PEEK();
//             if (VALUE_IS_FALSE(condition) || VALUE_IS_NULL(condition)) {
//                 DROP();
//             } else {
//                 ip -= offset; // 若条件为真则不再计算or的右操作数
//             }
//             LOOP();
//         }
//         CASE(CLOSE_UPVALUE):
//             // 栈顶：相当于局部变量
//             // 把地址大于栈顶局部变量的upvalue关闭
//             ClosedUpvalue(curThread, curThread->esp - 1);
//             DROP();
//             LOOP();
//         CASE(RETURN): {
//             // 栈顶 返回值
//             Value retVal = POP();
//             curThread->usedFrameNum --; // 从函数返回，该堆栈框架使用完毕，增加可用堆栈框架数据
//             ClosedUpvalue(curThread, stackStart);

//             // 如果一个堆栈框架都没用，说明它没有调用函数或者所有的函数调用都返回了，可以结束它
//             if (curThread->usedFrameNum == 0U) {
//                 // 如果不是被另一个线程调用的，就直接结束
//                 if (curThread->caller == NULL) {
//                     curThread->stack[0] = retVal;
//                     curThread->esp = curThread->stack + 1; // 丢弃其他结果
//                     return VM_RESULT_SUCCESS;
//                 } else {
//                     // else
//                 }
//                 // 恢复主调方线程的调度
//                 ObjThread *callerThread = curThread->caller;
//                 curThread->caller = NULL;
//                 curThread = callerThread;
//                 vm->curThread = callerThread;

//                 // 在主调线程的栈顶存储被调线程的执行结果
//                 curThread->esp[-1] = retVal;
//             } else {
//                 // 将返回值置于运行时栈栈顶
//                 stackStart[0] = retVal;
//                 curThread->esp = stackStart + 1; // 回收堆栈
//             }
//         }
//         CASE(CONSTRUCT): {
//             // 栈底 stackStart[0]=classPtr
//             // TODO:
//             ObjInstance *objInstance = NewObjInstance(vm, VALUE_TO_CLASS(stackStart[0]));
//             stackStart[0] = OBJ_TO_VALUE(objInstance);
//             LOOP();
//         }
//         CASE(CREATE_CLOSURE): {
//             // 指令流 2字节待创建闭包的函数在常量中的索引+函数所用的upvalue数乘2
            
//             // endCompileUnit已经将闭包函数添加进了常量表
//             ObjFn *fn = VALUE_TO_OBJFN(objFn->constants.datas[READ_SHORT()]);
//             ObjClosure * objClosure = NewObjClosure(vm, fn);
            
//             // 将创建好的闭包的value结构压到栈顶
//             // 先将其压到栈中，后面再创建upvalue，这样可避免在创建upvalue过程中被GC
//             PUSH(OBJ_TO_VALUE(objClosure));
//             uint32_t idx = 0U;
//             while (idx < fn->upvalueNum) {
//                 // 读入endcompileunit函数最后为每个upvalue写入的数据对儿
//                 uint8_t isEnclosingLocalVar = READ_BYTE();
//                 uint8_t index = READ_BYTE();

//                 if (isEnclosingLocalVar) { // 是直接外层的局部变量
//                     objClosure->upvalues[idx] = CreateOpenUpvalue(vm, curThread, curFrame->stackStart + index);
//                 } else {
//                     // 直接从父编译单元中继承
//                     objClosure->upvalues[idx] = curFrame->closure->upvalues[index];
//                 }
//                 idx ++;
//             }
//             LOOP();
//         }
//         CASE(CREATE_CLASS): {
//             // 指令流 1字节的field数量
//             // 栈顶 基类
//             // 次栈顶 子类名
//             uint32_t fieldNum = READ_BYTE();
//             Value superClass = curThread->esp[-1]; // 基类名
//             Value className = curThread->esp[-2]; // 子类名

//             // 回收基类所占的栈空间
//             // 次栈顶的空间暂时保留，创建的类会直接用该空间
//             DROP();
//             // 校验基类合法性
//             IsValidateSuperClass(vm, className, fieldNum, superClass);
//             Class *classPtr = NewClass(vm, VALUE_TO_OBJSTR(className), fieldNum, VALUE_TO_CLASS(superClass));

//             // 类存储于栈底
//             stackStart[0] = OBJ_TO_VALUE(classPtr);
//             LOOP();
//         }
//         CASE(INSTANCE_METHOD):
//         CASE(STATIC_METHOD): {
//             // 指令流 待绑定的方法 “名字” 在allMethodName中的索引
//             // 在栈顶 待绑定的类
//             // 次栈顶 待绑定的方法
//             uint32_t methodNameIndex = READ_SHORT();
//             Class *classPtr = VALUE_TO_CLASS(PEEK());
//             Value method = PEEK2();
//             BindMethodAndPatch(vm, opCode, methodNameIndex, classPtr, method);
//             DROP();
//             DROP();
//             LOOP();
//         }
//         CASE(END):
//             NOT_REACHED();
//     }
//     NOT_REACHED();

//     #undef PUSH
//     #undef POP
//     #undef DROP
//     #undef PEEK
//     #undef PEEK2
//     #undef LOAD_CUR_FRAME
//     #undef STORE_CUR_FRAME
//     #undef READ_BYTE
//     #undef READ_SHORT
// }