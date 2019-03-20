#pragma once

#include "Structs.h"
#ifndef _FUNCTION_H
#define _FUNCTION_H

typedef void*(*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int(*NvAPI_Initialize_t)();
typedef int(*NvAPI_Unload_t)();
typedef int(*NvAPI_EnumPhysicalGPUs_t)(int** handles, int* count);
typedef int(*NvAPI_GPU_GetSystemType_t)(int* handle, int* systype);
typedef int(*NvAPI_GPU_GetFullName_t)(int* handle, char* sysname);
typedef int(*NvAPI_GPU_GetPhysicalFrameBufferSize_t)(int* handle, int* memsize);
typedef int(*NvAPI_GPU_GetRamType_t)(int* handle, int* memtype);
typedef int(*NvAPI_GPU_GetVbiosVersionString_t)(int* handle, char* biosname);
typedef int(*NvAPI_GPU_GetAllClockFrequencies_t)(int* handle, NV_GPU_PERF_PSTATES20_INFO_V1* pstates_info);
typedef int(*NvAPI_GPU_GetPstates20_t)(int* handle, NV_GPU_PERF_PSTATES20_INFO_V1* pstates_info);
typedef int(*NvAPI_GPU_SetPstates20_t)(int* handle, int* pstates_info);
typedef int(*NvApi_SYS_GetChipSetInfo_t)(NV_CHIPSET_INFO_v4* p_chipset_info_v4);

NvAPI_QueryInterface_t NvQueryInterface = nullptr;
NvAPI_Initialize_t NvInit = nullptr;
NvAPI_Unload_t NvUnload = nullptr;
NvAPI_EnumPhysicalGPUs_t NvEnumGPUs = nullptr;
NvAPI_GPU_GetSystemType_t NvGetSysType = nullptr;
NvAPI_GPU_GetFullName_t NvGetName = nullptr;
NvAPI_GPU_GetPhysicalFrameBufferSize_t NvGetMemSize = nullptr;
NvAPI_GPU_GetRamType_t NvGetMemType = nullptr;
NvAPI_GPU_GetVbiosVersionString_t NvGetBiosName = nullptr;
NvAPI_GPU_GetAllClockFrequencies_t NvGetFreq = nullptr;
NvAPI_GPU_GetPstates20_t NvGetPstates = nullptr;
NvAPI_GPU_SetPstates20_t NvSetPstates = nullptr;
NvApi_SYS_GetChipSetInfo_t NvGetChipSetInfo = nullptr;

#endif