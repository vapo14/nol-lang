//
//  vm.h
//  ñol-lang
//
//  Created by Victor Padron on 06/04/24.
//

#ifndef vm_h
#define vm_h

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    // This instruction pointer will point directly into the bytecode array
    uint8_t* ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM(void);
void freeVM(void);
InterpretResult interpret(Chunk* chunk);

#endif /* vm_h */
