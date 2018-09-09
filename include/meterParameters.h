#pragma once
//
#include "pluginterfaces/vst/vsttypes.h"
//
namespace Carlsound
{
	namespace Meter
	{
		//-----------------------------------------------------------------------------
		// Global Parameters
		//-----------------------------------------------------------------------------
		// HERE are defined the parameter Ids which are exported to the host
		enum MeterParameters : Steinberg::Vst::ParamID
		{
			kParamLevel,
			kParamLevel2,
			kParamBypassId,
			//
			kNumGlobalParameters
		};
	} // namespace Meter
} // namespace Carlsound