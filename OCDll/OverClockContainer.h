#pragma once

#include "Structs.h"
#include "Internal.h"

class OverClockContainer
{
public:
	OverClockContainer() = default;
	~OverClockContainer() = default;
	NV_GPU_INFO Get_GPU_INFO() const;
	NV_OC_STATES GPUOverClock(int step) const;
	NV_OC_STATES VRAMOverClock(int step) const;
	Internal* internal = new Internal();
};
