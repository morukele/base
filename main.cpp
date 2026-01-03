#include "base.h"
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
    int foo[100];
    for (int i = 0; i < ArrayCount(foo); i += 1) {
        foo[i] = i;
    }

    EvalPrint(ArrayCount(foo));

    int bar[100];
    MemoryCopyArray(bar, foo);
    EvalPrint(bar[50]);
    EvalPrint(MemoryMatch(foo, bar, sizeof(foo)));
    MemoryZeroArray(bar);
    EvalPrint(bar[50]);
    EvalPrint(MemoryMatch(foo, bar, sizeof(foo)));

    EvalPrint(OffsetOfMember(TestStruct, a));
    EvalPrint(OffsetOfMember(TestStruct, b));
    EvalPrint(OffsetOfMember(TestStruct, c));
    EvalPrint(OffsetOfMember(TestStruct, d));

    TestStruct t = {1, 2, 3, 4};
    EvalPrint(t.a);
    EvalPrint(t.d);
    MemoryZeroStruct(&t);
    EvalPrint(t.a);
    EvalPrint(t.d);

    EvalPrint(Min(1, 10));
    EvalPrint(Min(100, 10));
    EvalPrint(Max(1, 10));
    EvalPrint(Min(100, 10));
    EvalPrint(Clamp(1, 10, 100));
    EvalPrint(Clamp(1, 0, 100));
    EvalPrint(Clamp(1, 500, 100));

    EvalPrint(min_I8);
    EvalPrint(min_I16);
    EvalPrint(min_I32);
    EvalPrintLL(min_I64);

    EvalPrint(max_I8);
    EvalPrint(max_I16);
    EvalPrint(max_I32);
    EvalPrintULL(max_I64);

    EvalPrintU(max_U8);
    EvalPrintU(max_U16);
    EvalPrintU(max_U32);
    EvalPrintULL(max_U64);

    EvalPrintF(machine_epsilon_F32);
    EvalPrintF(machine_epsilon_F64);

    return 0;
}