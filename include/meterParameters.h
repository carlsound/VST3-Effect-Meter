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
			kParameterColor,
			kParameterInputLevel,
			kParameterBypassId,
			//
			kQtyGlobalParameters
		};
	} // namespace Meter
} // namespace Carlsound