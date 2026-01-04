#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#define KB(x) x*1024

typedef struct
{
    /* data */
    char* buffer;
    uint64_t currentOffset;
    uint64_t bufferSize;
} Arena;

void ArenaInit(Arena* arena, uint64_t bufferSize);
void* ArenaAlloc(
    Arena* arena, 
    uint64_t numOfElement, 
    uint64_t elementSize, 
    uint64_t alignSize
);
void ArenaResetPointer(Arena* arena);
void ArenaDelete(Arena* arena);

#endif // ARENAA_H