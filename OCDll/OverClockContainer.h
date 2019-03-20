#pragma once

#include "Structs.h"

class OverClockContainer
{
public:
	static NV_GPU_INFO Get_GPU_INFO();
	static NV_OC_STATES GPUOverClock(int step);
	static NV_OC_STATES VRAMOverClock(int step);
};
