

#pragma once

#ifndef _countof
#    define _countof(x) (sizeof(x) / sizeof(x[0]))
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//
//			pfn
//
typedef int(__cdecl *pfn_vsnprintf)(
    char *const _Buffer,
    size_t const _BufferCount,
    char const *const _Format,
    va_list _ArgList);

int __cdecl _cinit(void);
void __cdecl _cexit(void);
void __cdecl _cinitfs(void);

typedef void(__cdecl *_PVFV)(void);
typedef int(__cdecl *_PIFV)(void);

int __cdecl atexit(_PVFV func);

void __cdecl free(void *ptr);
void *__cdecl malloc(size_t size); // NonPagedPool
void *__cdecl kmalloc(SIZE_T size, POOL_TYPE PoolType);

double __cdecl kstrtod(char const *_String, char **_EndPtr);
int __cdecl ksprintf(char *const s, size_t const sz, char const *const f, ...);

int __cdecl kfprintf(void *f, char const *const _Format, ...);

int __cdecl dprintf(const char *format, ...);

void __cdecl exit(_In_ int _Code);
void __cdecl _exit(_In_ int _Code);

//
// fs extend..
//

//参数3代表是否要转换成R3的那种路径
/*FILE**/ void *__cdecl fopen2(char const *_FileName, char const *_Mode, int _IsSanitizePath);
/*FILE**/ void *__cdecl fopenSafe(char const *_FileName, char const *_Mode, int _IsSanitizePath);

//参数2代表是否要转换成R3的那种路径
int __cdecl remove2(char const *_FileName, int _IsSanitizePath);

#ifdef __cplusplus
}
#endif // __cplusplus
