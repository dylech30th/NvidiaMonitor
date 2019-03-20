#pragma once

#include "Structs.h"

class _declspec(dllexport) Internal
{
public:
	NV_GPU_INFO Get_GPU_INFO() const;
	NV_OC_STATES GPUOverClock(int step);
	NV_OC_STATES VRAMOverClock(int step);
	Internal();
	~Internal() = default;
private:
	int nGPU = 0;
	int sys_type = 0;
	int mem_size = 0;
	int mem_type = 0;
	int* hdlGPU[64] = { nullptr }, *buf = nullptr;
	char sys_name[64] = { 0 };
	char bios_name[64] = { 0 };
	NV_GPU_PERF_PSTATES20_INFO_V1* pstates_info;
	NV_CHIPSET_INFO_v4* p_chipset_info_v4;

	NV_GPU_INFO* info_ = nullptr;

	void initialize();
};
