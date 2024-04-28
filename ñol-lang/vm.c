//
//  vm.c
//  ñol-lang
//
//  Created by Victor Padron on 06/04/24.
//

#include "common.h"

#include "vm.h"
#include "debug.h"
#include <stdio.h>

/** 
 A global instance of the VM is not suitable for real implementations.
 Ideally the host application(s) should have more control on this instance by taking a pointer
 to the vm rather than having a single global reference.
**/
VM vm;

static void resetStack(void) {
    vm.stackTop = vm.stack;
}

void initVM(void) {
    resetStack();
}

void freeVM(void) {
    
}

/**
    We add the value to the current stackTop position then increment the stackTop pointer
 */
void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

/**
    Moves the stack pointer back to get the most recent used slot.
    There's no need to remove the element from the array as it will simply
    be overwritten by whatever element is added afterwards.
 */
Value pop(void) {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run(void) {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
// this macro contains the while loop to wrap the statements in a single scope, while
// allowing the use of the semicolon at the end of the statement. i.e: "BINARY_OP();" would
// execute the statements inside the while loop.
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false)
    
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        // print each element in the stack
        printf("         ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        // convert ip back to a relative offset from the beginning of the bytecode to dissasemble
        // the instruction that starts at that byte
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = vm.chunk->constants.values[READ_BYTE()];
                push(constant);
                break;
            }
            case OP_ADD:        BINARY_OP(+); break;
            case OP_SUBTRACT:   BINARY_OP(-); break;
            case OP_MULTIPLY:   BINARY_OP(*); break;
            case OP_DIVIDE:     BINARY_OP(/); break;
            case OP_NEGATE:     push(-pop()); break;
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            default:
                break;
        }
    }
    
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
