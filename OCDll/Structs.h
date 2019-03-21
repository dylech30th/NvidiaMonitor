#pragma once
#ifndef _STRUCTS_H
#define _STRUCTS_H
#include <string>

typedef unsigned long NvU32;
typedef char NvAPI_ShortString[64];

struct NV_GPU_CLOCK_FREQUENCIES_V2
{
	NvU32   version;
	NvU32   ClockType : 2;
	NvU32   reserved : 22;
	NvU32   reserved1 : 8;
	struct
	{
		NvU32   bIsPresent : 1;
		NvU32   reserved : 31;
		NvU32   frequency;
	}domain[32];
};

typedef struct
{
	int value;
	struct
	{
		int   mindelta;
		int   maxdelta;
	} valueRange;
} NV_GPU_PERF_PSTATES20_PARAM_DELTA;

typedef struct
{
	NvU32   domainId;
	NvU32   typeId;
	NvU32   bIsEditable : 1;
	NvU32   reserved : 31;
	NV_GPU_PERF_PSTATES20_PARAM_DELTA   freqDelta_kHz;
	union
	{
		struct
		{
			NvU32   freq_kHz;
		} single;
		struct
		{
			NvU32   minFreq_kHz;
			NvU32   maxFreq_kHz;
			NvU32   domainId;
			NvU32   minVoltage_uV;
			NvU32   maxVoltage_uV;
		} range;
	} data;
} NV_GPU_PSTATE20_CLOCK_ENTRY_V1;

typedef struct
{
	NvU32   domainId;
	NvU32   bIsEditable : 1;
	NvU32   reserved : 31;
	NvU32   volt_uV;
	int     voltDelta_uV;
} NV_GPU_PSTATE20_BASE_VOLTAGE_ENTRY_V1;

typedef struct
{
	NvU32   version;
	NvU32   bIsEditable : 1;
	NvU32   reserved : 31;
	NvU32   numPstates;
	NvU32   numClocks;
	NvU32   numBaseVoltages;
	struct
	{
		NvU32                                   pstateId;
		NvU32                                   bIsEditable : 1;
		NvU32                                   reserved : 31;
		NV_GPU_PSTATE20_CLOCK_ENTRY_V1          clocks[8];
		NV_GPU_PSTATE20_BASE_VOLTAGE_ENTRY_V1   baseVoltages[4];
	} pstates[16];
} NV_GPU_PERF_PSTATES20_INFO_V1;

struct NV_CHIPSET_INFO_v4
{
	NvU32               version;            //!< structure version
	NvU32               vendorId;           //!< Chipset vendor identification
	NvU32               deviceId;           //!< Chipset device identification
	NvAPI_ShortString   szVendorName;       //!< Chipset vendor Name
	NvAPI_ShortString   szChipsetName;      //!< Chipset device Name
	NvU32               flags;              //!< Chipset info flags - obsolete
	NvU32               subSysVendorId;     //!< Chipset subsystem vendor identification
	NvU32               subSysDeviceId;     //!< Chipset subsystem device identification 
	NvAPI_ShortString   szSubSysVendorName; //!< subsystem vendor Name
	NvU32               HBvendorId;         //!< Host bridge vendor identification
	NvU32               HBdeviceId;         //!< Host bridge device identification
	NvU32               HBsubSysVendorId;   //!< Host bridge subsystem vendor identification
	NvU32               HBsubSysDeviceId;   //!< Host bridge subsystem device identification

};

typedef struct
{
	NvAPI_ShortString SystemType;
	NvU32 HBvendorId;
	NvU32 HbDeviceId;
	NvU32 HBsubSysDeviceId;
	NvU32 HBsubSysVendorId;
	NvU32 DeviceId;
	NvU32 Flags;
	NvU32 SubSysDeviceId;
	NvU32 SubSysVendorId;
	NvAPI_ShortString SzChipsetName;
	NvAPI_ShortString SzSubSysVendorName;
	NvAPI_ShortString SzVendorName;
	NvU32 VendorId;
	NvU32 Version;
	NvAPI_ShortString Name;
	int VRAM_Type;
	NvU32 VRAM_Size;
	NvAPI_ShortString BIOS_Name;
	NvU32 MaxFrequency;
	NvU32 MinFrequency;
	NvU32 RAM_Frequency;
	NvU32 Current_GPU_OC;
	NvU32 Current_RAM_OC;
} NV_GPU_INFO;

typedef enum
{
	OC_STATES_OK = 1,
	OC_STATES_FAILED = 0
} NV_OC_STATES;
#endif