#pragma once
//
#include "pluginterfaces/gui/iplugview.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/common/pluginview.h"
//
namespace Carlsound
{
	namespace Meter
	{
		class IMeterPluginView : public Steinberg::CPluginView
		{
		public:
			//------------------------------------------------------------------------
			/**  */
			virtual Steinberg::tresult PLUGIN_API setInputLevelFeedback(Steinberg::Vst::ParamValue newLevel) = 0;

			/**  */
			virtual Steinberg::tresult PLUGIN_API setColorFeedback(Steinberg::Vst::ParamValue newColor) = 0;

			//------------------------------------------------------------------------
			//---Interface------
			OBJ_METHODS(IMeterPluginView, CPluginView)
				
			DEFINE_INTERFACES
				DEF_INTERFACE(IPlugView)
			END_DEFINE_INTERFACES(CPluginView)
			
			REFCOUNT_METHODS(CPluginView)

		}; //class IMeterControllerView
	} // namespace Meter
} // namespace Carlsound