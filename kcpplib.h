#pragma once
//
// 外部导入
//

#include <fltKernel.h>

//-------------------------------------------------------
//  extern
//-------------------------------------------------------
EXTERN_C
PDRIVER_OBJECT g_pDriverObject;
EXTERN_C
wchar_t g_DriverRegistryKey[/*MAX_PATH*/ 260];
EXTERN_C
wchar_t g_DrvServiceKeyName[/*MAX_PATH*/ 260];
EXTERN_C
PVOID g_pDrvImageBase;
EXTERN_C
SIZE_T g_DrvImageSize;

//外部需要实现这个函数,此函数可以认为是调用者的DriverEntry
EXTERN_C
DRIVER_INITIALIZE KcpplibDriverEntry;

//外部需要实现这个函数,此函数可以认为是调用者的DriverUnLoad
EXTERN_C
DRIVER_UNLOAD KcpplibDriverUnLoad;

//-------------------------------------------------------
//  cppsupport
//-------------------------------------------------------
#ifdef __cplusplus
// kstl
#    include <kcpplib/kstl/kstl.h>
// kcrt
#    include <kcpplib/kcrt/kcrt.h>

#else
#    error 必须用CPP来引用我
#endif
