//
//  chunk.h
//  ñol-lang
//
//  Created by Victor Padron on 13/03/24.
//

/*
    Sequences of bytecode are referred to as "chunks"
 */
#ifndef chunk_h
#define chunk_h

#include "common.h"
#include "value.h"

// one-byte operation codes
typedef enum {
    OP_CONSTANT,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

typedef struct {
    // how many of the allocated entries are actually in use
    int count;
    // the number of elements in the array
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

// function to initialize a chunk
void initChunk(Chunk* chunk);
// function to append to the end of the chunk, includes the line
// that corresponds to the instruction
void writeChunk(Chunk* chunk, uint8_t byte, int line);
// function to free a chunk
void freeChunk(Chunk* chunk);
// function to add a constant to a chunk
int addConstant(Chunk* chunk, Value value);

#endif /* chunk_h */
