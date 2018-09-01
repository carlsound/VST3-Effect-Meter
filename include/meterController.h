#pragma once
//
#include "meterParameters.h"
#include "meterUIDs.h"
//
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
//
#include <string>
//
#if SMTG_OS_WINDOWS
#include <atlconv.h>
#include <tchar.h>
#endif
//
#include <codecvt>
#include <memory>
#include <string>
//
namespace Carlsound
{
	namespace Meter 
	{
	//-----------------------------------------------------------------------------
	class MeterController : public Steinberg::Vst::EditController
	{
		public:
		//------------------------------------------------------------------------
		// create function required for Plug-in factory,
		// it will be called to create new instances of this controller
		//------------------------------------------------------------------------
		static FUnknown* createInstance 
		(
			void*
		)
		{
			return (Steinberg::Vst::IEditController*) new MeterController ();
		}
		//
		///////////////////////////////////////////////////////////////////////////
		//---from IPluginBase--------
		Steinberg::tresult PLUGIN_API initialize 
		(
			FUnknown* context
		) 
			SMTG_OVERRIDE;
		//
			///////////////////////////////////////////////////////////////////////////
		//---from EditController-----
		Steinberg::tresult PLUGIN_API setComponentState 
		(
			Steinberg::IBStream* state
		) 
			SMTG_OVERRIDE;
		//
		Steinberg::Vst::ParamValue PLUGIN_API normalizedParamToPlain
		(
			Steinberg::Vst::ParamID tag, 
			Steinberg::Vst::ParamValue valueNormalized
		)
			SMTG_OVERRIDE;
		//
		Steinberg::Vst::ParamValue PLUGIN_API plainParamToNormalized
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value
		) 
			SMTG_OVERRIDE;
		//
		Steinberg::tresult PLUGIN_API getParamStringByValue
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized,
			Steinberg::Vst::String128 string
		) 
			SMTG_OVERRIDE;
		//
		///////////////////////////////////////////////////////////////////////////
		//---member variables----
		//std::shared_ptr<Steinberg::Vst::RangeParameter> m_speedRangeParameter;
		};
		//------------------------------------------------------------------------
	} // namespace Meter
} // namespace Carlsound
