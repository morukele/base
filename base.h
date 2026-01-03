#ifndef BASE_H
#define BASE_H

/*
 * Context cracking
 */
#if defined(_MSC_VER)
# define COMPILER_CL 1
# if defined(_WIN32)
#  define OS_WINDOWS 1
# else
#  error missing OS detection
# endif

# if defined(_M_AMD64)
#  define ARCH_AMD64 1
# elif defined(_M_I86)
#  define ARCH_X86 1
# else
#  error missing ARCH detection
# endif

#elif defined(__clang__)
# define COMPILER_CLANG 1
# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error missing OS detection
# endif

# if defined(__amd64__)
#  define ARCH_X64 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# else
#  error missing ARCH detection
# endif

#elif defined(__GNUC__)
# define COMPILER_GCC 1
# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error missing OS detection
# endif

# if defined(__amd64__) || defined(__x86_64__)
#  define ARCH_X64 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# else
#  error missing ARCH detection
# endif
#else
# error no context cracking for this compiler
#endif

/*
* Zero fill missing context macros
*/
#if !defined(COMPILER_CL)
# define COMPILER_CL 0
#endif
#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(OS_WINDOWS)
# define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
# define OS_LINUX 0
#endif
#if !defined(OS_MAC)
# define OS_MAC 0
#endif
#if !defined(ARCH_X64)
# define ARCH_X64 0
#endif
#if !defined(ARCH_AMD64)
# define ARCH_AMD64 0
#endif
#if !defined(ARCH_ARM64)
# define ARCH_ARM64 0
#endif

#if !defined(ENABLE_ASSERT)
# define ENABLE_ASSERT 0
#endif

/*
* Helper Macros
*/
#define Stmnt(S) do { S } while (0)

// This allows users to implement their own custom assert break
// instead of default crash behaviour.
#if !defined(AssertBreak)
# define AssertBreak() __builtin_trap()
#endif

#if ENABLE_ASSERT
# define Assert(c) Stmnt( if (!(c)){ AssertBreak(); } )
#else
# define Assert(c)
#endif

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#define ArrayCount(a) (sizeof(a)/sizeof(*(a)))

#define IntFromPtr(p) (unsigned long long)((char*)p - (char*)0)
#define PtrFromInt(n) (void*)((char*)0 + (n))


#define Member(T,m) (((T*)0)->m)
#define OffsetOfMember(T,m) IntFromPtr(&Member(T,m))

#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Max(a,b) (((a) > (b)) ? (a) : (b))
#define Clamp(a,x,b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) : (x))

#define ClampTop(a,b) Min(a,b)
#define ClampBot(a,b) Max(a,b)

#define global static
#define local static
#define function static

// Working with C style linkage
#define c_linkage_begin extern "C"{
#define c_linkage_end }
#define c_linkage extern "C"

#include <string.h>
#define MemoryZero(p,z) memset((p), 0, (z))
#define MemoryZeroStruct(p) MemoryZero((p), sizeof(*(p)))
#define MemoryZeroArray(p) MemoryZero((p), sizeof(p))
#define MemoryZeroTyped(p,c) MemoryZero((p), sizeof(*(p))*(c))

#define MemoryMatch(a,b,z) (memcmp((a), (b), (z))) == 0

#define MemoryCopy(d,s,z) memmove((d), (s), (z))
#define MemoryCopyStruct(d,s) MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s))))
#define MemoryCopyArray(d,s) MemoryCopy((d), (s), Min(sizeof(s), sizeof(d)))
#define MemoryCopyTyped(d,s,c) MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s)))*(c))

/*
* Basic Types
*/
#include <stdint.h>
typedef int8_t   I8;
typedef int16_t  I16;
typedef int32_t  I32;
typedef int64_t  I64;
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef float    F32;
typedef double   F64;

/*
 * Basic Constants
 */
global I8  min_I8  = (I8) 0x80;
global I16 min_I16 = (I16)0x8000;
global I32 min_I32 = (I32)0x80000000;
global I64 min_I64 = (I64)0x8000000000000000llu;

global I8  max_I8  = (I8) 0x7f;
global I16 max_I16 = (I16)0x7fff;
global I32 max_I32 = (I32)0x7fffffff;
global I64 max_I64 = (I64)0x7fffffffffffffffllu;

global U8  min_U8  = 0x80;
global U16 min_U16 = 0x8000;
global U32 min_U32 = 0x80000000;
global U64 min_U64 = 0x8000000000000000llu;

global U8  max_U8  = 0xff;
global U16 max_U16 = 0xffff;
global U32 max_U32 = 0xffffffff;
global U64 max_U64 = 0xffffffffffffffffllu;

global F32 machine_epsilon_F32 = 1.1920929e-7f;
global F64 machine_epsilon_F64 = 2.220446e-16f;

#endif //BASE_H