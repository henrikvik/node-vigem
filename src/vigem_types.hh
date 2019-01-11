#pragma once
#define RtlZeroMemory(ptr, size) memset(ptr, 0, size)
#define FORCEINLINE
#define VOID void
#define BOOL bool
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef short SHORT;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef unsigned long *PULONG;