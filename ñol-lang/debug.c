//
//  debug.c
//  ñol-lang
//
//  Created by Victor Padron on 13/03/24.
//

#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    
    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    // get the index of the constant pool where the constant is stored
    uint8_t constant = chunk->code[offset + 1];
    // print the opcode and the corresponding parameter
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    // returning the next offset, +2 since we read both the op instruction and the parameter from the chunk
    return offset + 2;
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}


int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    // if the offset is not the first instruction and it continues to
    // be part of the initial instruction (same line) print a pipe.
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        // should these whitespaces be dynamic ? what if we have 1000+ lines ?
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }
    
    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
