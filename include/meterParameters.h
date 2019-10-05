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
			kParameterInputLevel,
			kParameterThreshold,
			kParameterColor,
			kParameterBypassId,
			kParameterInputLevelFeedback,
			kParameterColorFeedback,
			//
			kQtyGlobalParameters
		};
	} // namespace Meter
} // namespace Carlsound