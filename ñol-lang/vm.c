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

void initVM(void) {
    
}

void freeVM(void) {
    
}

static InterpretResult run(void) {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        // convert ip back to a relative offset from the beginning of the bytecode to dissasemble
        // the instruction that starts at that byte
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = vm.chunk->constants.values[READ_BYTE()];
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN:
                return INTERPRET_OK;
            default:
                break;
        }
    }
    
#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
