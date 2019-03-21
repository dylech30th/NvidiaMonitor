#include "stdafx.h"
#include "OverClockContainer.h"
#include "Internal.h"

NV_GPU_INFO OverClockContainer::Get_GPU_INFO() const
{
	return internal->Get_GPU_INFO();
}

NV_OC_STATES OverClockContainer::GPUOverClock(int step) const
{
	return internal->GPUOverClock(step);
}

NV_OC_STATES OverClockContainer::VRAMOverClock(int step) const
{
	return internal->VRAMOverClock(step);
}
