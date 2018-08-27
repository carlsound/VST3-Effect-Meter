#pragma once

#include "public.sdk/samples/vst/mda-vst3/source/mdaParameter.h"
//
namespace Carlsound 
{
	namespace Meter 
	{
		// HERE are defined the parameter Ids which are exported to the host
		/*
		enum MeterParams : Steinberg::Vst::ParamID
		{
			kParamBypassId = 100,
			//kParamSpeedId = 102
		};
		 */

		// HERE you have to define new unique class ids: for processor and for controller
		// you can use GUID creator tools like https://www.guidgenerator.com/
		static const Steinberg::FUID MeterProcessorUID 
		(
			0x2A2EB6C2,
			0x6223431C,
			0x9F74777D,
			0x7ACA3544
		);
		//
		static const Steinberg::FUID MeterControllerUID 
		(
			0xE0B8B3C0,
			0xF24F47BC,
			0xAECFEA4C,
			0x7AC94115
		);
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
