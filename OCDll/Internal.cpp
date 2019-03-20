#include "stdafx.h"
#include <Windows.h>
#include "Internal.h"
#include "Structs.h"
#include "Functions.h"
#include <cstdlib>

#define _CRT_SECURE_NO_WARNINGS

NV_GPU_INFO Internal::Get_GPU_INFO() const
{
	info_->HBvendorId = p_chipset_info_v4->HBvendorId;
	info_->HbDeviceId = p_chipset_info_v4->HBdeviceId;
	info_->SubSysDeviceId = p_chipset_info_v4->subSysDeviceId;
	info_->SubSysVendorId = p_chipset_info_v4->subSysVendorId;
	info_->DeviceId = p_chipset_info_v4->deviceId;
	info_->Flags = p_chipset_info_v4->flags;
	info_->HBsubSysDeviceId = p_chipset_info_v4->HBsubSysDeviceId;
	info_->HBsubSysVendorId = p_chipset_info_v4->HBsubSysVendorId;
	memcpy(info_->SzChipsetName, p_chipset_info_v4->szChipsetName, sizeof p_chipset_info_v4->szChipsetName);
	memcpy(info_->SzSubSysVendorName, p_chipset_info_v4->szSubSysVendorName, sizeof p_chipset_info_v4->szSubSysVendorName);
	memcpy(info_->SzVendorName, p_chipset_info_v4->szVendorName, sizeof p_chipset_info_v4->szVendorName);
	info_->VendorId = p_chipset_info_v4->vendorId;
	info_->Version = p_chipset_info_v4->version;
	memcpy(info_->Name, sys_name, sizeof sys_name);
	info_->VRAM_Size = mem_size;
	info_->VRAM_Type = mem_type;
	memcpy(info_->BIOS_Name, bios_name, sizeof bios_name);
	info_->MaxFrequency = pstates_info->pstates[0].clocks[0].data.range.maxFreq_kHz / 1000;
	info_->MinFrequency = pstates_info->pstates[0].clocks[0].data.range.minFreq_kHz / 1000;
	info_->RAM_Frequency = pstates_info->pstates[0].clocks[1].data.single.freq_kHz / 1000;
	info_->Current_GPU_OC = pstates_info->pstates[0].clocks[0].freqDelta_kHz.value / 1000;
	info_->Current_RAM_OC = pstates_info->pstates[0].clocks[1].freqDelta_kHz.value / 1000;
	return *info_;
}

NV_OC_STATES Internal::GPUOverClock(const int step)
{
	if (step >= 500000 || step <= -500000)
	{
		return OC_STATES_FAILED;
	}
	buf = reinterpret_cast<int*>(malloc(0x1c94));
	memset(buf, 0, 0x1c94);
	buf[0] = 0x11c94;
	buf[2] = 1;
	buf[3] = 1;
	buf[10] = step;
	const auto states = NvSetPstates(hdlGPU[0], buf) ? OC_STATES_FAILED : OC_STATES_OK;
	free(buf);
	return states;
}

NV_OC_STATES Internal::VRAMOverClock(const int step)
{
	if (step >= 500000 || step <= -500000)
	{
		return OC_STATES_FAILED;
	}
	buf = reinterpret_cast<int*>(malloc(0x1c94));
	memset(buf, 0, 0x1c94);
	buf[0] = 0x11c94;
	buf[2] = 1;
	buf[3] = 1;
	buf[7] = 4;
	buf[10] = mem_type < 7 ? step : step * 2;
	const auto states = NvSetPstates(hdlGPU[0], buf) ? OC_STATES_FAILED : OC_STATES_OK;
	free(buf);
	return states;
}

Internal::Internal()
{
	initialize();
}

void Internal::initialize()
{
	pstates_info->version = 0x11c94;
	p_chipset_info_v4->version = static_cast<unsigned long>(sizeof(NV_CHIPSET_INFO_v4) | 4 << 16);
	NvQueryInterface = reinterpret_cast<NvAPI_QueryInterface_t>(GetProcAddress(LoadLibrary(L"nvapi.dll"), "nvapi_QueryInterface"));
	NvInit = reinterpret_cast<NvAPI_Initialize_t>(NvQueryInterface(0x0150E828));
	NvUnload = reinterpret_cast<NvAPI_Unload_t>(NvQueryInterface(0xD22BDD7E));
	NvEnumGPUs = reinterpret_cast<NvAPI_EnumPhysicalGPUs_t>(NvQueryInterface(0xE5AC921F));
	NvGetSysType = reinterpret_cast<NvAPI_GPU_GetSystemType_t>(NvQueryInterface(0xBAAABFCC));
	NvGetName = reinterpret_cast<NvAPI_GPU_GetFullName_t>(NvQueryInterface(0xCEEE8E9F));
	NvGetMemSize = reinterpret_cast<NvAPI_GPU_GetPhysicalFrameBufferSize_t>(NvQueryInterface(0x46FBEB03));
	NvGetMemType = reinterpret_cast<NvAPI_GPU_GetRamType_t>(NvQueryInterface(0x57F7CAAC));
	NvGetBiosName = reinterpret_cast<NvAPI_GPU_GetVbiosVersionString_t>(NvQueryInterface(0xA561FD7D));
	NvGetFreq = reinterpret_cast<NvAPI_GPU_GetAllClockFrequencies_t>(NvQueryInterface(0xDCB616C3));
	NvGetPstates = reinterpret_cast<NvAPI_GPU_GetPstates20_t>(NvQueryInterface(0x6FF81213));
	NvSetPstates = reinterpret_cast<NvAPI_GPU_SetPstates20_t>(NvQueryInterface(0x0F4DAE6B));
	NvGetChipSetInfo = reinterpret_cast<NvApi_SYS_GetChipSetInfo_t>(NvQueryInterface(0x53DABBCA));

	NvInit();
	NvEnumGPUs(hdlGPU, &nGPU);
	NvGetSysType(hdlGPU[0], reinterpret_cast<int*>(&sys_type));
	NvGetName(hdlGPU[0], sys_name);
	NvGetMemSize(hdlGPU[0], &mem_size);
	NvGetMemType(hdlGPU[0], &mem_type);
	NvGetBiosName(hdlGPU[0], bios_name);
	NvGetPstates(hdlGPU[0], pstates_info);
	NvGetChipSetInfo(p_chipset_info_v4);
}
