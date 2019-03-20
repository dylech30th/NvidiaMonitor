#include "stdafx.h"
#include "OverClockContainer.h"
#include "Internal.h"

Internal* internal = new Internal();

NV_GPU_INFO OverClockContainer::Get_GPU_INFO()
{
	return internal->Get_GPU_INFO();
}

NV_OC_STATES OverClockContainer::GPUOverClock(const int step)
{
	return internal->GPUOverClock(step);
}

NV_OC_STATES OverClockContainer::VRAMOverClock(const int step)
{
	return internal->VRAMOverClock(step);
}
