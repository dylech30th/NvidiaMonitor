// OCDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "OverClockContainer.h"


extern "C" __declspec(dllexport) NV_GPU_INFO __stdcall Get_GPU_INFO()
{
	return OverClockContainer::Get_GPU_INFO();
}

extern "C" __declspec(dllexport) NV_OC_STATES __stdcall GPUOverClock(const int step)
{
	return OverClockContainer::GPUOverClock(step);
}

extern "C" __declspec(dllexport) NV_OC_STATES __stdcall VRAMOverClock(const int step)
{
	return OverClockContainer::VRAMOverClock(step);
}
