//
//  value.h
//  ñol-lang
//
//  Created by Victor Padron on 16/03/24.
//

#ifndef value_h
#define value_h

#include "common.h"

typedef double Value;

/**
    Dynamic Array for constant pool
 */
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif /* value_h */
