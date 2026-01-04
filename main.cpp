#include "base.h"
#include "arena.h"
#include <stdio.h>

#define EvalPrint(x) printf("%s = %d\n", #x, (I32)(x))
#define EvalPrintLL(x) printf("%s = %lld\n", #x, (I64)(x))
#define EvalPrintU(x) printf("%s = %u\n", #x, (U32)(x))
#define EvalPrintULL(x) printf("%s = %llu\n", #x, (U64)(x))
#define EvalPrintF(x) printf("%s = %e\n", #x, (F64)(x))

struct TestStruct {
    int a;
    int b;
    int c;
    int d;
};

int main() {
    Arena arena = {};
    ArenaInit(&arena, KB(10));

    int* a = (int*)ArenaAlloc(&arena, 1, sizeof(int), _Alignof(int));
    char* b = (char*)ArenaAlloc(&arena, 100, sizeof(char), _Alignof(char));

    *a = 20;
    strcpy(b, "a string.");

    printf("%d\n", *a);
    printf("%s\n", b);

    ArenaDelete(&arena);

    // Should produce rubbish value
    printf("%d\n", *a);
    printf("%s\n", b);

    return 0;
}