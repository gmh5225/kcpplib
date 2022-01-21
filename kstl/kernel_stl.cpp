
#include "kstl_stdint.h"
#include "kernel_stl.h"
#include "kstlhead.h"

// crt
#include "../kcrt/kcrt.h"

////////////////////////////////////////////////////////////////////////////////
//
// macro utilities
//

////////////////////////////////////////////////////////////////////////////////
//
// constants and macros
//

/// A pool tag for this module
static const ULONG kKstlpPoolTag = 'LTSK';

////////////////////////////////////////////////////////////////////////////////
//
// types
//

////////////////////////////////////////////////////////////////////////////////
//
// prototypes
//

////////////////////////////////////////////////////////////////////////////////
//
// variables
//

////////////////////////////////////////////////////////////////////////////////
//
// implementations
//

// An alternative implmentation of a C++ exception handler. Issues a bug check.
_Use_decl_annotations_
DECLSPEC_NORETURN void
KernelStlRaiseException(ULONG bug_check_code)
{
    KdBreakPoint();
#pragma warning(push)
#pragma warning(disable : 28159)
    KeBugCheck(bug_check_code);
#pragma warning(pop)
}

// Followings are definitions of functions needed to link successfully.

/*_Use_decl_annotations_*/ DECLSPEC_NORETURN void __cdecl _invalid_parameter_noinfo_noreturn()
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}

namespace std {

// VS2019需要加
_CRTIMP2_PURE_IMPORT _Prhand _Raise_handler;

/*_Use_decl_annotations_*/ DECLSPEC_NORETURN void __cdecl _Xbad_alloc()
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}
_Use_decl_annotations_
DECLSPEC_NORETURN void __cdecl _Xinvalid_argument(_In_z_ const char *)
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}
_Use_decl_annotations_
DECLSPEC_NORETURN void __cdecl _Xlength_error(_In_z_ const char *)
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}
_Use_decl_annotations_
DECLSPEC_NORETURN void __cdecl _Xout_of_range(_In_z_ const char *)
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}
_Use_decl_annotations_
DECLSPEC_NORETURN void __cdecl _Xoverflow_error(_In_z_ const char *)
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}
_Use_decl_annotations_
DECLSPEC_NORETURN void __cdecl _Xruntime_error(_In_z_ const char *)
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}
_Use_decl_annotations_
DECLSPEC_NORETURN void __cdecl _Xbad_function_call()
{
    KernelStlRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}

_Use_decl_annotations_
char const *__cdecl _Syserror_map(__in int)
{
    // DbgBreakPoint();
    //__debugbreak();
    return nullptr;
}

//_Use_decl_annotations_ char const*
//	__cdecl
//	_Winerror_map(
//		__in int
//	)
//{
//	//DbgBreakPoint();
//	//__debugbreak();
//	return nullptr;
//}
//_Use_decl_annotations_
// int __CLRCALL_PURE_OR_CDECL _Winerror_map(int)
//{
//	return nullptr;
//}
} // namespace std

_Use_decl_annotations_
void *__cdecl
operator new[](size_t size)
{
    if (size == 0)
    {
        size = 1;
    }

    void *p = malloc(size);
    if (!p)
    {
        KernelStlRaiseException(MUST_SUCCEED_POOL_EMPTY);
    }
    return p;
}
// An alternative implmentation of the new operator
_Use_decl_annotations_
void *__cdecl
operator new(size_t size)
{
    if (size == 0)
    {
        size = 1;
    }

    void *p = malloc(size);
    if (!p)
    {
        KernelStlRaiseException(MUST_SUCCEED_POOL_EMPTY);
    }
    return p;
}

// An alternative implmentation of the new operator
_Use_decl_annotations_
void __cdecl
operator delete(void *p)
{
    if (p)
    {
        free(p);
    }
}

// An alternative implmentation of the new operator
_Use_decl_annotations_
void __cdecl
operator delete(void *p, size_t size)
{
    UNREFERENCED_PARAMETER(size);
    if (p)
    {
        free(p);
    }
}
_Use_decl_annotations_
void __cdecl
operator delete[](_In_ void *p)
{
    if (p)
    {
        free(p);
    }
}
// An alternative implmentation of __stdio_common_vsprintf_s
_Use_decl_annotations_
EXTERN_C
int __cdecl __stdio_common_vsprintf_s(
    unsigned __int64 _Options,
    char *_Buffer,
    size_t _BufferCount,
    char const *_Format,
    _locale_t _Locale,
    va_list _ArgList)
{
    UNREFERENCED_PARAMETER(_Options);
    UNREFERENCED_PARAMETER(_Locale);

    // Calls _vsnprintf exported by ntoskrnl
    using _vsnprintf_type = int __cdecl(char *, size_t, const char *, va_list);
    static _vsnprintf_type *local__vsnprintf = nullptr;
    if (!local__vsnprintf)
    {
        UNICODE_STRING proc_name_U = {};
        /*
        _vsnprintf
        */
        unsigned char s[] = {

            0x3a, 0x51, 0x4e, 0x49, 0x4b, 0x4d, 0x44, 0x49, 0x4f, 0x41, 0xdb};

        for (unsigned int m = 0; m < sizeof(s); ++m)
        {
            unsigned char c = s[m];
            c += 0x25;
            s[m] = c;
        }

        std::string str((char *)s);
        std::wstring wstr(str.begin(), str.end());
        RtlInitUnicodeString(&proc_name_U, wstr.data());
        local__vsnprintf = reinterpret_cast<_vsnprintf_type *>(MmGetSystemRoutineAddress(&proc_name_U));
    }

    return local__vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
}

// An alternative implmentation of __stdio_common_vsprintf
_Use_decl_annotations_
EXTERN_C
int __cdecl __stdio_common_vsprintf(
    unsigned __int64 _Options,
    char *_Buffer,
    size_t _BufferCount,
    char const *_Format,
    _locale_t _Locale,
    va_list _ArgList)
{
    return __stdio_common_vsprintf_s(_Options, _Buffer, _BufferCount, _Format, _Locale, _ArgList);
}

// An alternative implmentation of __stdio_common_vswprintf_s
_Use_decl_annotations_
EXTERN_C
int __cdecl __stdio_common_vswprintf_s(
    unsigned __int64 _Options,
    wchar_t *_Buffer,
    size_t _BufferCount,
    wchar_t const *_Format,
    _locale_t _Locale,
    va_list _ArgList)
{
    UNREFERENCED_PARAMETER(_Options);
    UNREFERENCED_PARAMETER(_Locale);

    // Calls _vsnwprintf exported by ntoskrnl
    using _vsnwprintf_type = int __cdecl(wchar_t *, size_t, const wchar_t *, va_list);
    static _vsnwprintf_type *local__vsnwprintf = nullptr;
    if (!local__vsnwprintf)
    {
        UNICODE_STRING proc_name_U = {};
        /*
        _vsnwprintf
        */
        unsigned char s[] = {

            0x5f, 0x75, 0x71, 0x6b, 0x73, 0x6b, 0x6c, 0x62, 0x66, 0x6b, 0x5c, 0xf5};

        for (unsigned int m = 0; m < sizeof(s); ++m)
        {
            unsigned char c = s[m];
            c += (unsigned char)m;
            s[m] = c;
        }

        std::string str((char *)s);
        std::wstring wstr(str.begin(), str.end());
        RtlInitUnicodeString(&proc_name_U, wstr.data());
        local__vsnwprintf = reinterpret_cast<_vsnwprintf_type *>(MmGetSystemRoutineAddress(&proc_name_U));
    }

    return local__vsnwprintf(_Buffer, _BufferCount, _Format, _ArgList);
}

// An alternative implmentation of __stdio_common_vswprintf
_Use_decl_annotations_
EXTERN_C
int __cdecl __stdio_common_vswprintf(
    unsigned __int64 _Options,
    wchar_t *_Buffer,
    size_t _BufferCount,
    wchar_t const *_Format,
    _locale_t _Locale,
    va_list _ArgList)
{
    return __stdio_common_vswprintf_s(_Options, _Buffer, _BufferCount, _Format, _Locale, _ArgList);
}

_ACRTIMP int __cdecl __stdio_common_vfprintf(
    _In_ unsigned __int64 _Options,
    _Inout_ FILE *_Stream,
    _In_z_ _Printf_format_string_params_(2) char const *_Format,
    _In_opt_ _locale_t _Locale,
    va_list _ArgList)
{
    return 1;
}

// lua 需要的(其实是eastl)
void *
operator new[](size_t size, const char *, int, unsigned, const char *, int)
{
    return malloc(size);
}
void *
operator new[](size_t size, size_t, size_t, const char *, int, unsigned, const char *, int)
{
    return malloc(size);
}
