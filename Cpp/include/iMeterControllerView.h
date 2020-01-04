#pragma once
//
#include "pluginterfaces/gui/iplugview.h"
//
namespace Carlsound
{
	namespace Meter
	{
		Class iMeterControllerView : Steinberg::IPlugView
		{
		public:
			//------------------------------------------------------------------------
			/**  */
			virtual Steinberg::tresult PLUGIN_API setInputLevelFeedback(Steinberg::Vst::ParamValue newLevel) = 0;

			/**  */
			virtual Steinberg::tresult PLUGIN_API setColorFeedback(Steinberg::Vst::ParamValue newColor) = 0;

		}; //class IMeterControllerView
	} // namespace Meter
} // namespace Carlsound