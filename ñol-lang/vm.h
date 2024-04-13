//
//  vm.h
//  ñol-lang
//
//  Created by Victor Padron on 06/04/24.
//

#ifndef vm_h
#define vm_h

#include "chunk.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    // This instruction pointer will point directly into the bytecode array
    uint8_t* ip;
    // VM Stack
    Value stack[STACK_MAX];
    // stackTop will point to where the next value will go
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM(void);
void freeVM(void);
InterpretResult interpret(Chunk* chunk);
// stack operations
void push(Value value);
Value pop(void);

#endif /* vm_h */
