//
//  debug.h
//  ñol-lang
//
//  Created by Victor Padron on 13/03/24.
//

#ifndef debug_h
#define debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif /* debug_h */
