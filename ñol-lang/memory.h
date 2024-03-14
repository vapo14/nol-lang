//
//  memory.h
//  ñol-lang
//
//  Created by Victor Padron on 13/03/24.
//

#ifndef memory_h
#define memory_h

#include "common.h"

// macro for growing capacity by doubling the capacity each time
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);


#endif /* memory_h */
