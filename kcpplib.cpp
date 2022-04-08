#include "kcpplib.h"

#include <fltKernel.h>
#include <ntimage.h>

#define NTSTRSAFE_LIB
#define NTSTRSAFE_NO_CB_FUNCTIONS
#include <ntstrsafe.h>

//-------------------------------------------------------
//  global
//-------------------------------------------------------
PDRIVER_OBJECT g_pDriverObject = NULL;
PVOID g_pDrvImageBase = NULL;
SIZE_T g_DrvImageSize = 0;
wchar_t g_DriverRegistryKey[/*MAX_PATH*/ 260];
wchar_t g_DrvServiceKeyName[/*MAX_PATH*/ 260];

//-------------------------------------------------------
//  internel function
//-------------------------------------------------------
void
OnUnload(__in DRIVER_OBJECT *driverObject)
{
    UNREFERENCED_PARAMETER(driverObject);

    //调用 外部提供
    KcpplibDriverUnLoad(driverObject);

    _cexit();
}

EXTERN_C
NTSTATUS
DriverEntry(__in DRIVER_OBJECT *driverObject, __in UNICODE_STRING *registryPath)
{
    //
    //	struct
    //

    typedef struct _KLDR_DATA_TABLE_ENTRY_COMMON
    {
        LIST_ENTRY InLoadOrderLinks;
        PVOID ExceptionTable;
        ULONG ExceptionTableSize;
        // ULONG padding on IA64
        PVOID GpValue;
        PNON_PAGED_DEBUG_INFO NonPagedDebugInfo;
        PVOID DllBase;
        PVOID EntryPoint;
        ULONG SizeOfImage;
        UNICODE_STRING FullDllName;
        UNICODE_STRING BaseDllName;
        ULONG Flags;
        USHORT LoadCount;
        USHORT __Unused5;
        PVOID SectionPointer;
        ULONG CheckSum;
        // ULONG padding on IA64
        PVOID LoadedImports;
        PVOID PatchInformation;
    } KLDR_DATA_TABLE_ENTRY_COMMON, *PKLDR_DATA_TABLE_ENTRY_COMMON;

    //
    // Do Base Operation
    //

    NTSTATUS ns = STATUS_UNSUCCESSFUL;

    if (_cinit() != 0)
    {
        //这里存在潜在的风险(理论100%成功，失败需要GG)
        // return STATUS_APP_INIT_FAILURE;
    }

    if (driverObject)
    {
        driverObject->DriverUnload = (DRIVER_UNLOAD *)(OnUnload);

        g_pDriverObject = driverObject;

        KLDR_DATA_TABLE_ENTRY_COMMON *pEntry = (KLDR_DATA_TABLE_ENTRY_COMMON *)(g_pDriverObject->DriverSection);
        if (pEntry)
        {
            g_pDrvImageBase = pEntry->DllBase;
            g_DrvImageSize = (SIZE_T)pEntry->SizeOfImage;

            RtlSecureZeroMemory(g_DrvServiceKeyName, sizeof(g_DrvServiceKeyName));

            wchar_t wtemp[] = {//%wZ
                               L'%',
                               L'w',
                               L'Z',
                               0,
                               0};

            RtlStringCchPrintfW(
                g_DrvServiceKeyName,
                RTL_NUMBER_OF(g_DrvServiceKeyName),
                wtemp,
                &driverObject->DriverExtension->ServiceKeyName);

            //修正PsSetCreateProcessNotifyRoutineEx返回STATUS_ACCESS_DENIED
            *(PULONG)((PCHAR)driverObject->DriverSection + 13 * sizeof(void *)) |= 0x20;
        }
        else
        {
            //防止被人抹去
            ns = STATUS_VIRUS_DELETED;
            goto _exit;
        }
    }

    if (registryPath)
    {
        if (registryPath != (UNICODE_STRING *)-1)
        {
            RtlSecureZeroMemory(g_DriverRegistryKey, sizeof(g_DriverRegistryKey));

            wchar_t wtemp[] = {//%wZ
                               L'%',
                               L'w',
                               L'Z',
                               0,
                               0};

            RtlStringCchPrintfW(g_DriverRegistryKey, RTL_NUMBER_OF(g_DriverRegistryKey), wtemp, registryPath);
        }
    }
    else
    {
        //防止被人无模块加载利用
        ns = STATUS_VIRUS_INFECTED;
        goto _exit;
    }

    //调用外部提供者
    ns = KcpplibDriverEntry(driverObject, registryPath);

_exit:
    return ns;
}
