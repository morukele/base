#include "arena.h"

void ArenaInit(Arena *arena, uint64_t bufferSize)
{
    *arena = (Arena){
        .buffer = (char *)malloc(bufferSize),
        .bufferSize = bufferSize,
        .currentOffset = 0};
}

void *ArenaAlloc(
    Arena *arena,
    uint64_t numOfElement,
    uint64_t elementSize,
    uint64_t alignSize)
{
    if (alignSize == 0 || (alignSize & (alignSize - 1)) == 1)
    {
        return NULL;
    }

    uintptr_t allocationSize = numOfElement * elementSize;

    if (allocationSize < elementSize)
    {
        return NULL;
    }

    uintptr_t totalOffset = (uintptr_t)arena->currentOffset + (uintptr_t)arena->buffer;
    uintptr_t padding = (~totalOffset + 1) & (alignSize - 1);

    totalOffset += padding;
    if (
        totalOffset + allocationSize >
        (uintptr_t)arena->bufferSize + (uintptr_t)arena->buffer)
    {
        return NULL;
    }

    arena->currentOffset += (padding + allocationSize);
    memset((void *)totalOffset, 0, allocationSize);

    return (void *)totalOffset;
}

void ArenaResetPointer(Arena* arena) {
    arena->currentOffset = 0;
    memset(arena->buffer, 0, arena->bufferSize);
}

void ArenaDelete(Arena* arena) {
    arena->currentOffset = 0;
    free(arena->buffer);
}