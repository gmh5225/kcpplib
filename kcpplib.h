#pragma once
//
// �ⲿ����
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

//�ⲿ��Ҫʵ���������,�˺���������Ϊ�ǵ����ߵ�DriverEntry
EXTERN_C
DRIVER_INITIALIZE KcpplibDriverEntry;

//�ⲿ��Ҫʵ���������,�˺���������Ϊ�ǵ����ߵ�DriverUnLoad
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
#    error ������CPP��������
#endif
